using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DeckLinkPlugin
{
    public class DeckLinkInput : MonoBehaviour
    {
        IntPtr _inputStream;
        Texture2D _texture;
        [SerializeField] RenderTexture _targetTexture;

        void OnEnable()
        {
            Debug.Log(DeckLinkCApi.GetVersionString());
            IntPtr devices;
            Debug.Log(DeckLinkCApi.ListDevices(out devices));
            Debug.Log(devices);
            IntPtr device = DeckLinkCApi.GetDevice(devices, 0);
            Debug.Log(device);
            Debug.Log(DeckLinkCApi.GetDeviceModelName(device));
            Debug.Log(DeckLinkCApi.GetDeviceDisplayName(device));
            _inputStream = DeckLinkCApi.CreateInputStream(device);
            Debug.Log(_inputStream);
            DeckLinkCApi.StartInputStream(_inputStream);

            _texture = new Texture2D(16, 16, TextureFormat.ARGB32, false);
        }

        void OnDisable()
        {
            DeckLinkCApi.StopInputStream(_inputStream);
            DeckLinkCApi.Release(_inputStream);
        }

        void Update()
        {
            // Get current frame
            var videoFrame = DeckLinkCApi.GetInputStreamVideoFrame(_inputStream);

            if (videoFrame == IntPtr.Zero)
                return;

            // Get frame data
            int width = DeckLinkCApi.GetVideoFrameWidth(videoFrame);
            int height = DeckLinkCApi.GetVideoFrameHeight(videoFrame);
            int rowBytes = DeckLinkCApi.GetVideoFrameRowBytes(videoFrame);
            var bytes = DeckLinkCApi.GetVideoFrameBytes(videoFrame);

            // Resize texture
            if (_texture.width != width || _texture.height != height)
                _texture.Resize(width, height, TextureFormat.ARGB32, false);

            // Apply data
            _texture.LoadRawTextureData(bytes, height * rowBytes);
            _texture.Apply();

            // Copy to target render texture
            if (_targetTexture)
            {
                RenderTexture.active = _targetTexture;
                Graphics.Blit(_texture, _targetTexture);
            }
        }
    }
}
