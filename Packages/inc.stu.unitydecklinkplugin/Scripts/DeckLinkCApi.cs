using System;
using System.Runtime.InteropServices;

namespace DeckLinkPlugin
{
    public class DeckLinkCApi
    {
        // Get version
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVersion")]
        internal static extern int GetVersion();

        // Get verson string
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVersionString")]
        private static extern IntPtr _GetVersionString();
        public static string GetVersionString()
        {
            return Marshal.PtrToStringAnsi(_GetVersionString());
        }

        // Add ref
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_AddRef")]
        internal static extern void AddRef(IntPtr obj);

        // Release
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_Release")]
        internal static extern void Release(IntPtr obj);


        // List devices
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_ListDevices")]
        internal static extern int ListDevices(out IntPtr devices);

        // Get device
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetDevice")]
        internal static extern IntPtr GetDevice(IntPtr devices, int index);

        // Get device model name
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetDeviceModelName")]
        private static extern IntPtr _GetDeviceModelName(IntPtr device);
        public static string GetDeviceModelName(IntPtr device)
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
                return Marshal.PtrToStringBSTR(_GetDeviceModelName(device));
            else
                return Marshal.PtrToStringAnsi(_GetDeviceModelName(device));
        }

        // Get device display name
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetDeviceDisplayName")]
        private static extern IntPtr _GetDeviceDisplayName(IntPtr device);
        public static string GetDeviceDisplayName(IntPtr device)
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
                return Marshal.PtrToStringBSTR(_GetDeviceDisplayName(device));
            else
                return Marshal.PtrToStringAnsi(_GetDeviceDisplayName(device));
        }

        // Create device input stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_CreateDeviceInputStream")]
        internal static extern IntPtr CreateDeviceInputStream(IntPtr device);

        // Input stream start
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_InputStreamStart")]
        internal static extern void InputStreamStart(IntPtr stream);

        // Input stream stop
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_InputStreamStop")]
        internal static extern void InputStreamStop(IntPtr stream);

        // Get input stream video frame
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetInputStreamVideoFrame")]
        internal static extern IntPtr GetInputStreamVideoFrame(IntPtr stream);
    }
}
