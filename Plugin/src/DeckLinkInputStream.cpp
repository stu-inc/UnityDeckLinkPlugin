#include "DeckLinkInputStream.hpp"
#include <thread>

DeckLinkInputStream::DeckLinkInputStream(IDeckLink *device)
    : IDeckLinkInputCallback() {

  // Get input
  if (device->QueryInterface(IID_IDeckLinkInput, (LPVOID *)&_input) != S_OK)
    _input = nullptr;
}

HRESULT DeckLinkInputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkInputStream::AddRef() { return ++_counter; }

ULONG DeckLinkInputStream::Release() {

  if (--_counter == 0) {

    // Release input
    if (_input)
      _input->Release();

    // Delete
    delete this;
  }
  
  return _counter;
}

void DeckLinkInputStream::Start() {}

void DeckLinkInputStream::Stop() {}

HRESULT
DeckLinkInputStream::VideoInputFormatChanged(
    /* in */ BMDVideoInputFormatChangedEvents notificationEvents,
    /* in */ IDeckLinkDisplayMode *newDisplayMode,
    /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags) {

  return S_OK;
}

HRESULT DeckLinkInputStream::VideoInputFrameArrived(
    /* in */ IDeckLinkVideoInputFrame *videoFrame,
    /* in */ IDeckLinkAudioInputPacket *audioPacket) {

  return S_OK;
}
