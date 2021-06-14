using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DeckLinkPlugin
{
    public class DeckLinkInput : MonoBehaviour
    {
        enum PixelFormat
        {
            YUV422_8bit = 0x32767579,
            ARGB32_8bit = 32
        }

        IntPtr _inputStream;
        Texture2D _texture;
        [SerializeField] PixelFormat _pixelFormat = PixelFormat.ARGB32_8bit;
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
            DeckLinkCApi.SetInputStreamPixelFormat(_inputStream, (int)_pixelFormat);
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
                Graphics.Blit(_texture, _targetTexture, new Vector2(1f, -1f), new Vector2(0, 0));
            }
        }
    }
}
