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

            DrawDefaultInspector();

            if (obj.Texture)
                EditorGUI.DrawPreviewTexture(new Rect(25, 60, 100, 100), obj.Texture);
        }
    }
#endif
}
