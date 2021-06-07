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

HRESULT DeckLinkInputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkInputStream::AddRef() { return ++_counter; }

ULONG DeckLinkInputStream::Release() {

  if (--_counter == 0) {
    delete this;
    return 0;
  }

  return _counter;
}

void DeckLinkInputStream::Lock() { _mutex.lock(); }

void DeckLinkInputStream::Unlock() { _mutex.unlock(); }

void DeckLinkInputStream::Start() {

  if (!_input)
    return;

  // Set callback
  _input->SetCallback(this);

  // Enable video input
  _input->EnableVideoInput(bmdModeHD1080p5994, bmdFormat8BitYUV,
                           bmdVideoInputEnableFormatDetection);

  // Start stream
  _input->StartStreams();
}

void DeckLinkInputStream::Stop() {

  if (!_input)
    return;

  // Stop stream
  _input->StopStreams();

  // Disable video input
  _input->DisableVideoInput();

  // Remove callback
  _input->SetCallback(nullptr);
}

IDeckLinkVideoFrame *DeckLinkInputStream::VideoFrame() { return _videoFrame; }

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

  Lock();
  _videoFrame = videoFrame;
  Unlock();

  return S_OK;
}
