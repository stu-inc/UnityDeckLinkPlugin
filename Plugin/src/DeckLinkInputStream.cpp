#include "DeckLinkInputStream.hpp"
#include <thread>

DeckLinkInputStream::DeckLinkInputStream(IDeckLink *device)
    : IDeckLinkInputCallback() {

  // Get input
  if (device->QueryInterface(IID_IDeckLinkInput, (LPVOID *)&_input) == S_OK)
    _input->SetCallback(this);
  else
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

void DeckLinkInputStream::Start() {

  if (!_input)
    return;
  
  // Enable video input
  _input->EnableVideoInput(bmdModeHD1080p5994, bmdFormat8BitYUV, bmdVideoInputEnableFormatDetection);

  // Start stream
  _input->StartStreams();
}

void DeckLinkInputStream::Stop() {

  if (!_input)
    return;

  // Disable video input
  _input->DisableVideoInput();

  // Stop stream
  _input->StopStreams();
}

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
