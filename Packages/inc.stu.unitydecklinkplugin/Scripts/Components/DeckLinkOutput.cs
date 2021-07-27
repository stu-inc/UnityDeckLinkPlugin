using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

namespace DeckLinkPlugin
{
    public class DeckLinkOutput : MonoBehaviour
    {
        enum PixelFormat
        {
            YUV422_8bit = 0x32767579,
            ARGB32_8bit = 32
        }

        [SerializeField] private int _deviceIndex = 0;
        [SerializeField] RenderTexture _targetTexture;
        private IntPtr _outputStream;

        void OnEnable()
        {
            IntPtr devices;
            Debug.Log(DeckLinkCApi.ListDevices(out devices));
            IntPtr device = DeckLinkCApi.GetDevice(devices, _deviceIndex);
            _outputStream = DeckLinkCApi.CreateOutputStream(device);

            DeckLinkCApi.StartOutputStream(_outputStream);

            // Start upload loop
            StartCoroutine("UploadTexture");
        }

        void OnDisable()
        {
            if (_outputStream != IntPtr.Zero)
            {
                DeckLinkCApi.StopOutputStream(_outputStream);
                DeckLinkCApi.Release(_outputStream);
                _outputStream = IntPtr.Zero;
            }
        }

        private IEnumerator UploadTexture()
        {
            while (true)
            {
                // Wait for end of frame
                yield return new WaitForEndOfFrame();

                if (_targetTexture == null)
                    continue;

                // Get target texture data
                AsyncGPUReadback.Request(_targetTexture, 0, (request) =>
                {
                    var data = request.GetData<byte>();
                    DeckLinkCApi.AddOutputStreamVideoFrame(_outputStream, data, 1920, 1080, 32);
                    Debug.Log(data.Length);
                });
            }
        }
    }
}
