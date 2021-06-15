#include "DeckLinkManager.hpp"

DeckLinkManager *DeckLinkManager::GetInstance() {
  static DeckLinkManager instance;
  static bool initialize = false;
  if (!initialize) {
    instance.Initialize();
    initialize = true;
  }
  return &instance;
}

void DeckLinkManager::Initialize() {

  // List devices
  _devices = ListDevices();
}

const std::vector<IDeckLink *> *DeckLinkManager::GetDevices() const {
  return &_devices;
}

std::vector<IDeckLink *> DeckLinkManager::ListDevices() const {

  std::vector<IDeckLink *> devices;

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
    return devices;

  IDeckLink *deckLink = nullptr;

  while (deckLinkIterator->Next(&deckLink) == S_OK)
    devices.push_back(deckLink);

  deckLinkIterator->Release();

  return devices;
}
