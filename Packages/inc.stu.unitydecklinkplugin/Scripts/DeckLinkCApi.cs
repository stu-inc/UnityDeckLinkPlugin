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
            return Marshal.PtrToStringAnsi(_GetDeviceModelName(device));
        }

        // Get device display name
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetDeviceDisplayName")]
        private static extern IntPtr _GetDeviceDisplayName(IntPtr device);
        public static string GetDeviceDisplayName(IntPtr device)
        {
            return Marshal.PtrToStringAnsi(_GetDeviceDisplayName(device));
        }
    }
}
