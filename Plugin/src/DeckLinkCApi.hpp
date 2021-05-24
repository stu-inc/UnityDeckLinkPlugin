#pragma once

class IDeckLink;

#ifdef __cplusplus
extern "C" {
#endif

// Get version
int DeckLink_GetVersion();

// Get version string
const char *DeckLink_GetVersionString();

// List devices
int DeckLink_ListDevices(IDeckLink *devices);

#ifdef __cplusplus
}
#endif
