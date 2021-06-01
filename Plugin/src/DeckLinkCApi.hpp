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

// Create device input stream
void *DeckLink_CreateDeviceInputStream(void *device);

// Release device input stream
void DeckLink_ReleaseDeviceInputStream(void *stream);

// Input stream start
void DeckLink_InputStreamStart(void *stream);

// Input stream stop
void DeckLink_InputStreamStop(void *stream);

// Get Video Frame
void *DeckLink_GetInputStreamVideoFrame(void *stream);

#ifdef __cplusplus
}
#endif
