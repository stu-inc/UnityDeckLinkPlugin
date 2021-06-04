#include "DeckLinkOutputStream.hpp"
#include <thread>

DeckLinkOutputStream::DeckLinkOutputStream(IDeckLink *device)
    : IDeckLinkVideoOutputCallback() {

  // Get output
  if (device->QueryInterface(IID_IDeckLinkOutput, (LPVOID *)&_output) == S_OK)
    _output->SetScheduledFrameCompletionCallback(this);
  else
    _output = nullptr;
}

HRESULT DeckLinkOutputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkOutputStream::AddRef() { return ++_counter; }

ULONG DeckLinkOutputStream::Release() {

  if (--_counter == 0) {

    // Release output
    if (_output)
      _output->Release();

    // Delete
    delete this;
  }

  return _counter;
}

void DeckLinkOutputStream::Lock() { _mutex.lock(); }

void DeckLinkOutputStream::Unlock() { _mutex.unlock(); }

void DeckLinkOutputStream::Start() {

  if (!_output)
    return;

  // Enable video output
  //_output->EnableVideoOutput(bmdModeHD1080p5994, bmdFormat8BitYUV,
  //                          bmdVideoOutputFlagDefault);

  // Start stream
  //_output->StartScheduledPlayback();
}

void DeckLinkOutputStream::Stop() {

  if (!_output)
    return;

  // Disable video output
  _output->DisableVideoOutput();

  // Stop stream
  //_output->StopScheduledPlayback();
}

HRESULT DeckLinkOutputStream::ScheduledFrameCompleted(
    /* in */ IDeckLinkVideoFrame *completedFrame,
    /* in */ BMDOutputFrameCompletionResult result) {

  return S_OK;
}

HRESULT DeckLinkOutputStream::ScheduledPlaybackHasStopped() { return S_OK; }
