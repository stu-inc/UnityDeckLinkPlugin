#pragma once

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

// Get device display name
const char *DeckLink_GetDeviceDisplayName(void *device);

#ifdef __cplusplus
}
#endif
