using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DeckLinkPlugin
{
    public class DeckLinkInput : MonoBehaviour
    {
        IntPtr _inputStream;

        void OnEnable()
        {
            Debug.Log(DeckLinkCApi.GetVersionString());
            IntPtr devices = new IntPtr();
            Debug.Log(DeckLinkCApi.ListDevices(out devices));
            Debug.Log(devices);
            IntPtr device = DeckLinkCApi.GetDevice(devices, 0);
            Debug.Log(device);
            Debug.Log(DeckLinkCApi.GetDeviceModelName(device));
            Debug.Log(DeckLinkCApi.GetDeviceDisplayName(device));
            _inputStream = DeckLinkCApi.CreateDeviceInputStream(device);
            Debug.Log(_inputStream);
            DeckLinkCApi.InputStreamStart(_inputStream);
        }

        void OnDisable()
        {
            DeckLinkCApi.InputStreamStop(_inputStream);
            DeckLinkCApi.ReleaseDeviceInputStream(_inputStream);
        }

        // Update is called once per frame
        void Update()
        {
        }
    }
}
