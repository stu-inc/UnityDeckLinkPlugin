using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
#if UNITY_EDITOR
using UnityEditor;
#endif

namespace DeckLinkPlugin
{
#if UNITY_EDITOR
    [CustomEditor(typeof(DeckLinkInput))] 
    public class DeckLinkInputEditor : Editor
    {
        public override void OnInspectorGUI()
        {
            var obj = target as DeckLinkInput;

            obj.DeviceIndex = EditorGUILayout.Popup("Device", obj.DeviceIndex, DeckLinkCApi.GetDeviceDisplayNames().ToArray());

            DrawDefaultInspector();
        }
    }
#endif
}
