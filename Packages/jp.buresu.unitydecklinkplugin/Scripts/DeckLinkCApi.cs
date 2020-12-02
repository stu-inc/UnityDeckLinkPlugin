using System.Runtime.InteropServices;

namespace DeckLinkPlugin
{
    public class DeckLinkCApi
    {
        [DllImport("DeckLinkPlugin")]
        internal static extern int DeckLink_Test();
    }
}
