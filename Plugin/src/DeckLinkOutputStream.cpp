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

  if (!--_counter) {
    delete this;
    return 0;
  }

  return _counter;
}

void DeckLinkOutputStream::AddVideoFrame(IDeckLinkVideoFrame *frame) {
  _mutex.lock();
  frame->AddRef();
  _videoFrames.push_back(frame);
  _mutex.unlock();
}

void DeckLinkOutputStream::Start() {

  if (!_output)
    return;

  // Set callback
  _output->SetScheduledFrameCompletionCallback(this);

  // Get display mode
  IDeckLinkDisplayModeIterator *displayModeIterator = nullptr;
  IDeckLinkDisplayMode *displayMode = nullptr;

  if (_output->GetDisplayModeIterator(&displayModeIterator) == S_OK)
    return;

  while (displayModeIterator->Next(&displayMode) == S_OK) {
    if (displayMode->GetDisplayMode() == _displayMode)
      break;
    displayMode = nullptr;
  }

  displayModeIterator->Release();

  if (!displayMode)
    return;

  // Enable video output
  _output->EnableVideoOutput(displayMode->GetDisplayMode(),
                             bmdVideoOutputFlagDefault);

  // Start stream
  _output->StartScheduledPlayback(0, 1, 1);
}

void DeckLinkOutputStream::Stop() {

  if (!_output)
    return;

  // Stop stream
  _output->StopScheduledPlayback(0, nullptr, 1);

  // Disable video output
  _output->DisableVideoOutput();

  // Remove callback
  _output->SetScheduledFrameCompletionCallback(nullptr);
}

BMDDisplayMode DeckLinkOutputStream::GetDisplayMode() const {
  return _displayMode;
}

void DeckLinkOutputStream::SetDisplayMode(BMDDisplayMode displayMode) {
  _displayMode = displayMode;
}

HRESULT DeckLinkOutputStream::ScheduledFrameCompleted(
    /* in */ IDeckLinkVideoFrame *completedFrame,
    /* in */ BMDOutputFrameCompletionResult result) {

  return S_OK;
}

HRESULT DeckLinkOutputStream::ScheduledPlaybackHasStopped() { return S_OK; }
