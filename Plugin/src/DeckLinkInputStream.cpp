#include "DeckLinkInputStream.hpp"
#include <thread>

DeckLinkInputStream::DeckLinkInputStream(IDeckLink *device)
    : IDeckLinkInputCallback() {

  // Get input
  if (device->QueryInterface(IID_IDeckLinkInput, (LPVOID *)&_input) != S_OK)
    _input = nullptr;
}

DeckLinkInputStream::~DeckLinkInputStream() {

  // Release input
  if (_input)
    _input->Release();
}

void DeckLinkInputStream::Start() {

  std::thread th(&DeckLinkInputStream::Run, this);
  th.join();
}

void DeckLinkInputStream::Stop() {}

void DeckLinkInputStream::Run() {}

HRESULT DeckLinkInputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkInputStream::AddRef() { return S_OK; }

ULONG DeckLinkInputStream::Release() { return S_OK; }

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
