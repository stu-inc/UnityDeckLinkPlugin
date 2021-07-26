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

// Start input stream
void DeckLink_StartInputStream(void *stream);

// Stop input stream
void DeckLink_StopInputStream(void *stream);

// Get input stream time stamp
long long int DeckLink_GetInputStreamTimeStamp(void *stream);

// Get input stream video frame
void *DeckLink_GetInputStreamVideoFrame(void *stream);

// Get input stream pixel format
int DeckLink_GetInputStreamPixelFormat(void *stream);

// Set input stream pixel format
void DeckLink_SetInputStreamPixelFormat(void *stream, int pixelFormat);

// Get video frame width
int DeckLink_GetVideoFrameWidth(void *frame);

// Get video frame height
int DeckLink_GetVideoFrameHeight(void *frame);

// Get video frame row bytes
int DeckLink_GetVideoFrameRowBytes(void *frame);

// Get video frame bytes
void *DeckLink_GetVideoFrameBytes(void *frame);

// Get video frame pixel format
int DeckLink_GetVideoFramePixelFormat(void *frame);

// Create output stream
void *DeckLink_CreateOutputStream(void *device);

// Start output stream
void DeckLink_StartOutputStream(void *stream);

// Stop output stream
void DeckLink_StopOutputStream(void *stream);

// Add output stream video frame
void DeckLink_AddOutputStreamVideoFrame(void *stream, void *data, int width,
                                        int height, int pixelFormat);

#ifdef __cplusplus
}
#endif
