using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

namespace DeckLinkPlugin
{
    public class DeckLinkOutput : MonoBehaviour
    {
        [SerializeField] RenderTexture _targetTexture;

        void OnEnable()
        {
            // Start upload loop
            StartCoroutine("UploadTexture");
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
                    Debug.Log(data.Length);
                });
            }

            yield return null;
        }
    }
}
