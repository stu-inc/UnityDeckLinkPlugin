using System;
using System.Collections;
using System.Threading;
using UnityEngine;

namespace UnityDeckLinkPlugin
{
    public class DeckLinkTimeStep : MonoBehaviour
    {
        private enum SyncMode { Internal }
        private enum FrameRate { _2398fps, _24fps, _25fps, _2997fps, _30fps, _4795fps, _48fps, _50fps, _5994fps, _60fps, _9590fps, _96fps, _100fps, _11988fps, _120fps }

        [SerializeField] private SyncMode _syncMode = SyncMode.Internal;
        [SerializeField] private FrameRate _frameRate = FrameRate._5994fps;
        private System.Diagnostics.Stopwatch _stopWatch = new System.Diagnostics.Stopwatch();
        private bool _genlocked = false;
        private bool _debug = false;

        private void Start()
        {
            QualitySettings.vSyncCount = 0;
            Application.targetFrameRate = 9999;
            _stopWatch.Restart();
            StartCoroutine("WaitForNextFrame");
        }

        private void Update()
        {
            if (Input.GetKeyDown(KeyCode.D))
                _debug = !_debug;
        }

        private void OnGUI()
        {
            if (_debug)
            {
                GUI.skin.label.fontSize = 50;
                GUILayout.Label("Genlocked:" + _genlocked.ToString());
                GUILayout.Label("Fps:" + (1f / Time.deltaTime).ToString("0.00"));
            }
        }

        private double GetCurrentTime()
        {
            return (1000.0 * (double)_stopWatch.Elapsed.Ticks) / (double)System.Diagnostics.Stopwatch.Frequency;
        }

        private double GetOneFrameTimeMS()
        {
            if (_frameRate == FrameRate._2398fps)
                return 1001.0 / 24.0;
            else if (_frameRate == FrameRate._24fps)
                return 1000.0 / 24.0;
            else if (_frameRate == FrameRate._25fps)
                return 1000.0 / 25.0;
            else if (_frameRate == FrameRate._2997fps)
                return 1001.0 / 30.0;
            else if (_frameRate == FrameRate._30fps)
                return 1000.0 / 30.0;
            else if (_frameRate == FrameRate._4795fps)
                return 1001.0 / 48.0;
            else if (_frameRate == FrameRate._48fps)
                return 1000.0 / 48.0;
            else if (_frameRate == FrameRate._50fps)
                return 1000.0 / 50.0;
            else if (_frameRate == FrameRate._5994fps)
                return 1001.0 / 60.0;
            else if (_frameRate == FrameRate._60fps)
                return 1000.0 / 60.0;
            else if (_frameRate == FrameRate._9590fps)
                return 1001.0 / 96.0;
            else if (_frameRate == FrameRate._96fps)
                return 1000.0 / 96.0;
            else if (_frameRate == FrameRate._100fps)
                return 1000.0 / 100.0;
            else if (_frameRate == FrameRate._11988fps)
                return 1001.0 / 120.0;
            else if (_frameRate == FrameRate._120fps)
                return 1000.0 / 120.0;

            return 0.0;
        }

        private long GetLastGenlockedTime()
        {
            // TODO
            return -1;
        }

        private IEnumerator WaitForNextFrame()
        {
            double lastFrameTime = GetCurrentTime();

            while (true)
            {
                // Update last genlocked time
                long lastGenlockedTime = GetLastGenlockedTime();

                // Wait for rendering
                yield return new WaitForEndOfFrame();

                // Sleep for frame
                double renderingTime = GetCurrentTime() - lastFrameTime;
                double sleepTime = Math.Max(GetOneFrameTimeMS() - renderingTime - 10.0, 0);
                Thread.Sleep((int)sleepTime);

                if (lastGenlockedTime < 0 || _syncMode == SyncMode.Internal)
                {
                    // Update status
                    _genlocked = false;

                    // Wait for frame
                    while (GetCurrentTime() - lastFrameTime < GetOneFrameTimeMS()) { }
                }
                else
                {
                    // Update status
                    _genlocked = true;

                    // Wait for genlocked frame
                    while (GetLastGenlockedTime() == lastGenlockedTime && GetCurrentTime() - lastFrameTime < GetOneFrameTimeMS() * 2) { }
                }

                // Update last frame time
                lastFrameTime = GetCurrentTime();
            }
        }
    }
}