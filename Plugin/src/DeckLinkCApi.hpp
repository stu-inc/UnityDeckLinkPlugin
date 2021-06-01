#pragma once

#if defined(WIN32)
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Get version
int DeckLink_GetVersion();

// Get version string
const char *DeckLink_GetVersionString();

// AddRef
void DeckLink_AddRef(void *obj);

// Release
void DeckLink_Release(void *obj);

// List devices
int DeckLink_ListDevices(void **devices);

// Get device
void *DeckLink_GetDevice(void **devices, int index);

// Get device model name
#if defined(WIN32)
BSTR DeckLink_GetDeviceModelName(void *device);
#else
const char *DeckLink_GetDeviceModelName(void *device);
#endif

// Get device display name
#if defined(WIN32)
BSTR DeckLink_GetDeviceDisplayName(void *device);
#else
const char *DeckLink_GetDeviceDisplayName(void *device);
#endif

// Create input stream
void *DeckLink_CreateInputStream(void *device);

// Lock input stream
void DeckLink_LockInputStream(void *stream);

// Unlock input stream
void DeckLink_UnlockInputStream(void *stream);

// Start input stream
void DeckLink_StartInputStream(void *stream);

// Stop input stream
void DeckLink_StopInputStream(void *stream);

// Get input stream video frame
void *DeckLink_GetInputStreamVideoFrame(void *stream);

// Get video frame width
int DeckLink_GetVideoFrameWidth(void *frame);

// Get video frame height
int DeckLink_GetVideoFrameHeight(void *frame);

// Get video frame row bytes
int DeckLink_GetVideoFrameRowBytes(void *frame);

// Get video frame bytes
void *DeckLink_GetVideoFrameBytes(void *frame);

#ifdef __cplusplus
}
#endif
