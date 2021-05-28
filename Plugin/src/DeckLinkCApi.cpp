#include "DeckLinkCApi.hpp"
#include <DeckLinkAPI.h>
#include <DeckLinkAPIVersion.h>
#include <vector>

int DeckLink_GetVersion() { return BLACKMAGIC_DECKLINK_API_VERSION; }

const char *DeckLink_GetVersionString() {
  return BLACKMAGIC_DECKLINK_API_VERSION_STRING;
}

int DeckLink_ListDevices(void **devices) {

  static std::vector<void *> d;

  d.clear();

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

  while (deckLinkIterator->Next(&deckLink) == S_OK)
    d.push_back(deckLink);

  deckLinkIterator->Release();

  if (!d.empty())
    *devices = d.data();

  return int(d.size());
}
