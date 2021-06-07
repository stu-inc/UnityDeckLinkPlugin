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
        [SerializeField] Material _targetMaterial;

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

        void Start()
        {
            _texture = new Texture2D(1920, 1080, TextureFormat.ARGB32, false);
            if (_targetMaterial)
                _targetMaterial.mainTexture = _texture;
        }

        void OnDisable()
        {
            DeckLinkCApi.StopInputStream(_inputStream);
            DeckLinkCApi.Release(_inputStream);
        }

        void Update()
        {
            var videoFrame = DeckLinkCApi.GetInputStreamVideoFrame(_inputStream);
            Debug.Log(DeckLinkCApi.GetVideoFrameWidth(videoFrame));
            Debug.Log(DeckLinkCApi.GetVideoFrameHeight(videoFrame));
            int rowBytes = DeckLinkCApi.GetVideoFrameRowBytes(videoFrame);
            var texData = DeckLinkCApi.GetVideoFrameBytes(videoFrame);
            Debug.Log(rowBytes);
            Debug.Log(texData);

            _texture.LoadRawTextureData(texData, 1920 * 1080 * 4);
            _texture.Apply();

            if (_targetTexture)
            {
                RenderTexture.active = _targetTexture;
                //_targetTexture.enableRandomWrite = true;
                Graphics.Blit(_texture, _targetTexture);
            }
        }
    }
}
