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
            Debug.Log(DeckLinkCApi.DeckLink_Test());
        }

        // Update is called once per frame
        void Update()
        {
        }
    }
}
