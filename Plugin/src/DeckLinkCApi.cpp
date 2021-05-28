#include "DeckLinkCApi.hpp"
#include <DeckLinkAPI.h>
#include <DeckLinkAPIVersion.h>

// Global variables
static int _numDevices = 0;
static void *_devices[32] = {nullptr};

int DeckLink_GetVersion() { return BLACKMAGIC_DECKLINK_API_VERSION; }

const char *DeckLink_GetVersionString() {
  return BLACKMAGIC_DECKLINK_API_VERSION_STRING;
}

int DeckLink_ListDevices(void **devices) {

  // Clear devices
  _numDevices = 0;
  *_devices = {nullptr};

  // List devices
  IDeckLinkIterator *deckLinkIterator = nullptr;

#if defined(WIN32)
  CoInitializeEx(NULL, COINIT_MULTITHREADED);
  CoCreateInstance(CLSID_CDeckLinkIterator, NULL, CLSCTX_ALL,
                   IID_IDeckLinkIterator, (void **)&deckLinkIterator);
#else
  deckLinkIterator = CreateDeckLinkIteratorInstance();
#endif

  if (!deckLinkIterator)
    return 0;

  IDeckLink *deckLink = nullptr;

  while (deckLinkIterator->Next(&deckLink) == S_OK) {
    _devices[_numDevices] = deckLink;
    _numDevices++;
  }

  deckLinkIterator->Release();

  // Set devices
  *devices = _numDevices > 0 ? _devices : nullptr;

  return _numDevices;
}

void *DeckLink_GetDevice(void **devices, int index) { return devices[index]; }

const char *DeckLink_GetDeviceDisplayName(void *device) {
  const char *name = "";
  if (device)
    ((IDeckLink *)device)->GetDisplayName(&name);
  return name;
}
