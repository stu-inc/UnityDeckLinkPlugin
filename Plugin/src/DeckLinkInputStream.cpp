#include "DeckLinkInputStream.hpp"
#include "DeckLinkVideoConverter.hpp"
#include "DeckLinkVideoFrame.hpp"

DeckLinkInputStream::DeckLinkInputStream(IDeckLink *device)
    : IDeckLinkInputCallback(), _device(device) {

  // Add ref
  _device->AddRef();

  // Get input
  if (_device->QueryInterface(IID_IDeckLinkInput, (LPVOID *)&_input) != S_OK)
    _input = nullptr;

  // Create video converter
  _videoConverter = new DeckLinkVideoConverter;

  // Create video frame
  _videoFrame = new DeckLinkVideoFrame(1920, 1080, bmdFormat8BitARGB);
}

DeckLinkInputStream::~DeckLinkInputStream() {

  // Release video frame
  _videoFrame->Release();

  // Release video converter
  _videoConverter->Release();

  // Release input
  if (_input)
    _input->Release();

  // Release device
  _device->Release();
}

HRESULT DeckLinkInputStream::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkInputStream::AddRef() { return ++_counter; }

ULONG DeckLinkInputStream::Release() {

  if (!--_counter) {
    delete this;
    return 0;
  }

  return _counter;
}

void DeckLinkInputStream::Start() {

  if (!_input)
    return;

  // Set callback
  _input->SetCallback(this);

  // Enable video input
  _input->EnableVideoInput(bmdModeHD1080p5994, _pixelFormat,
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

IDeckLinkVideoFrame *DeckLinkInputStream::GetVideoFrame() {
  return _videoFrame;
}

BMDPixelFormat DeckLinkInputStream::GetPixelFormat() const {
  return _pixelFormat;
}

void DeckLinkInputStream::SetPixelFormat(BMDPixelFormat pixelFormat) {
  _pixelFormat = pixelFormat;
}

HRESULT
DeckLinkInputStream::VideoInputFormatChanged(
    /* in */ BMDVideoInputFormatChangedEvents notificationEvents,
    /* in */ IDeckLinkDisplayMode *newDisplayMode,
    /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags) {

  if (notificationEvents & bmdVideoInputColorspaceChanged ||
      notificationEvents & bmdVideoInputDisplayModeChanged) {
    _input->FlushStreams();
    _input->StopStreams();
    _input->EnableVideoInput(newDisplayMode->GetDisplayMode(), _pixelFormat,
                             bmdVideoInputEnableFormatDetection);
  }

  return _input->StartStreams();
}

HRESULT DeckLinkInputStream::VideoInputFrameArrived(
    /* in */ IDeckLinkVideoInputFrame *videoFrame,
    /* in */ IDeckLinkAudioInputPacket *audioPacket) {

  return _videoConverter->ConvertFrame(videoFrame, _videoFrame);
}
