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
            _inputStream = DeckLinkCApi.CreateInputStream(device);
            Debug.Log(_inputStream);
            DeckLinkCApi.StartInputStream(_inputStream);
        }

        void OnDisable()
        {
            DeckLinkCApi.StopInputStream(_inputStream);
            DeckLinkCApi.Release(_inputStream);
        }

        void Update()
        {
            DeckLinkCApi.LockInputStream(_inputStream);
            var videoFrame = DeckLinkCApi.GetInputStreamVideoFrame(_inputStream);
            Debug.Log(DeckLinkCApi.GetVideoFrameWidth(videoFrame));
            Debug.Log(DeckLinkCApi.GetVideoFrameHeight(videoFrame));
            DeckLinkCApi.UnlockInputStream(_inputStream);
        }
    }
}
