using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using UnityEngine;
using Unity.Collections;
using Unity.Collections.LowLevel.Unsafe;

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

        public static List<string> GetDeviceDisplayNames()
        {
            IntPtr devices;
            int num = ListDevices(out devices);
            var names = new List<string>();
            for (int i = 0; i < num; ++i)
            {
                var device = GetDevice(devices, i);
                names.Add(GetDeviceDisplayName(device));
            }
            return names;
        }

        // Create input stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_CreateInputStream")]
        internal static extern IntPtr CreateInputStream(IntPtr device);

        // Start input stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_StartInputStream")]
        internal static extern void StartInputStream(IntPtr stream);

        // Stop input stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_StopInputStream")]
        internal static extern void StopInputStream(IntPtr stream);

        // Get input stream time stamp
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetInputStreamTimeStamp")]
        internal static extern long GetInputStreamTimeStamp(IntPtr stream);

        // Get input stream video frame
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetInputStreamVideoFrame")]
        internal static extern IntPtr GetInputStreamVideoFrame(IntPtr stream);

        // Get input stream pixel format
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetInputStreamPixelFormat")]
        internal static extern int GetInputStreamPixelFormat(IntPtr stream);

        // Set input stream pixel format
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_SetInputStreamPixelFormat")]
        internal static extern void SetInputStreamPixelFormat(IntPtr stream, int pixelFormat);

        // Get video frame width
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVideoFrameWidth")]
        internal static extern int GetVideoFrameWidth(IntPtr frame);

        // Get video frame height
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVideoFrameHeight")]
        internal static extern int GetVideoFrameHeight(IntPtr frame);

        // Get video frame row bytes
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVideoFrameRowBytes")]
        internal static extern int GetVideoFrameRowBytes(IntPtr frame);

        // Get video frame bytes
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVideoFrameBytes")]
        internal static extern IntPtr GetVideoFrameBytes(IntPtr frame);

        // Get video frame pixel format
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_GetVideoFramePixelFormat")]
        internal static extern int GetVideoFramePixelFormat(IntPtr frame);

        // Create output stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_CreateOutputStream")]
        internal static extern IntPtr CreateOutputStream(IntPtr device);

        // Start output stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_StartOutputStream")]
        internal static extern void StartOutputStream(IntPtr stream);

        // Stop input stream
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_StopOutputStream")]
        internal static extern void StopOutputStream(IntPtr stream);

        // Add output stream video frame
        [DllImport("DeckLinkPlugin", EntryPoint = "DeckLink_AddOutputStreamVideoFrame")]
        internal static extern void _AddOutputStreamVideoFrame(IntPtr stream, IntPtr data, int width, int height, int pixelFormat);
        public static unsafe void AddOutputStreamVideoFrame(IntPtr stream, NativeArray<byte> data, int width, int height, int pixelFormat)
        {
            var ptr = NativeArrayUnsafeUtility.GetUnsafeReadOnlyPtr(data);
            _AddOutputStreamVideoFrame(stream, new IntPtr(ptr), width, height, pixelFormat);
        }
    }
}
