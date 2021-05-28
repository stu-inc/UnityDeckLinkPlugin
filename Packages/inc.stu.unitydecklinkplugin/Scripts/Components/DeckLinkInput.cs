using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DeckLinkPlugin
{
    public class DeckLinkInput : MonoBehaviour
    {
        // Start is called before the first frame update
        void Start()
        {
            Debug.Log("hoge!");
            Debug.Log(DeckLinkCApi.GetVersionString());
            IntPtr devices = new IntPtr();
            Debug.Log(DeckLinkCApi.ListDevices(out devices));
            Debug.Log(devices);
        }

        // Update is called once per frame
        void Update()
        {
        }
    }
}
