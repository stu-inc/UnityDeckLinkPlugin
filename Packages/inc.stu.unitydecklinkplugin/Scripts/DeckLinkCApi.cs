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
    }
}
