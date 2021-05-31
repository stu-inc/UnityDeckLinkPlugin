#include "DeckLinkInputStream.hpp"

DeckLinkInputStream::DeckLinkInputStream() : IDeckLinkInputCallback() {}

DeckLinkInputStream::~DeckLinkInputStream() {}

HRESULT DeckLinkInputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return 0;
}

ULONG DeckLinkInputStream::AddRef() { return 0; }

ULONG DeckLinkInputStream::Release() { return 0; }

HRESULT
DeckLinkInputStream::VideoInputFormatChanged(
    /* in */ BMDVideoInputFormatChangedEvents notificationEvents,
    /* in */ IDeckLinkDisplayMode *newDisplayMode,
    /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags) {

  return 0;
}

HRESULT DeckLinkInputStream::VideoInputFrameArrived(
    /* in */ IDeckLinkVideoInputFrame *videoFrame,
    /* in */ IDeckLinkAudioInputPacket *audioPacket) {

  return 0;
}
