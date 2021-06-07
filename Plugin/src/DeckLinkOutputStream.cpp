#include "DeckLinkOutputStream.hpp"
#include <thread>

DeckLinkOutputStream::DeckLinkOutputStream(IDeckLink *device)
    : IDeckLinkVideoOutputCallback(), _device(device) {

  // Add ref
  _device->AddRef();

  // Get output
  if (device->QueryInterface(IID_IDeckLinkOutput, (LPVOID *)&_output) != S_OK)
    _output = nullptr;
}

DeckLinkOutputStream::~DeckLinkOutputStream() {

  // Release output
  if (_output)
    _output->Release();

  // Release device
  _device->Release();
}

HRESULT DeckLinkOutputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkOutputStream::AddRef() { return ++_counter; }

ULONG DeckLinkOutputStream::Release() {

  if (--_counter == 0) {
    delete this;
    return 0;
  }

  return _counter;
}

void DeckLinkOutputStream::Lock() { _mutex.lock(); }

void DeckLinkOutputStream::Unlock() { _mutex.unlock(); }

void DeckLinkOutputStream::Start() {

  if (!_output)
    return;

  // Set callback
  _output->SetScheduledFrameCompletionCallback(this);

  // Enable video output
  //_output->EnableVideoOutput(bmdModeHD1080p5994, bmdFormat8BitYUV,
  //                          bmdVideoOutputFlagDefault);

  // Start stream
  //_output->StartScheduledPlayback();
}

void DeckLinkOutputStream::Stop() {

  if (!_output)
    return;

  // Stop stream
  //_output->StopScheduledPlayback();

  // Disable video output
  _output->DisableVideoOutput();

  // Remove callback
  _output->SetScheduledFrameCompletionCallback(nullptr);
}

HRESULT DeckLinkOutputStream::ScheduledFrameCompleted(
    /* in */ IDeckLinkVideoFrame *completedFrame,
    /* in */ BMDOutputFrameCompletionResult result) {

  return S_OK;
}

HRESULT DeckLinkOutputStream::ScheduledPlaybackHasStopped() { return S_OK; }
