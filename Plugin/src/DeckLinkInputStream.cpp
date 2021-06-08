#include "DeckLinkInputStream.hpp"
#include "DeckLinkVideoFrame.hpp"

#include <string.h>

DeckLinkInputStream::DeckLinkInputStream(IDeckLink *device)
    : IDeckLinkInputCallback(), _device(device) {

  // Add ref
  _device->AddRef();

  // Get input
  if (_device->QueryInterface(IID_IDeckLinkInput, (LPVOID *)&_input) != S_OK)
    _input = nullptr;

    // Create video converter
#if defined(WIN32)
  CoCreateInstance(CLSID_CDeckLinkVideoConversion, NULL, CLSCTX_ALL,
                   IID_IDeckLinkVideoConversion, (LPVOID *)&_videoConverter);
#else
  _videoConverter = CreateVideoConversionInstance();
#endif

  _videoFrame = new DeckLinkVideoFrame(1920, 1080, bmdFormat8BitARGB);
}

DeckLinkInputStream::~DeckLinkInputStream() {

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
  _input->EnableVideoInput(bmdModeHD1080p5994, bmdFormat8BitARGB,
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

  if (notificationEvents & bmdVideoInputColorspaceChanged ||
      notificationEvents & bmdVideoInputDisplayModeChanged) {
    _input->FlushStreams();
    _input->StopStreams();
    _input->EnableVideoInput(newDisplayMode->GetDisplayMode(),
                             bmdFormat8BitARGB,
                             bmdVideoInputEnableFormatDetection);
  }

  return _input->StartStreams();
}

HRESULT DeckLinkInputStream::VideoInputFrameArrived(
    /* in */ IDeckLinkVideoInputFrame *videoFrame,
    /* in */ IDeckLinkAudioInputPacket *audioPacket) {

  void *data;
  videoFrame->GetBytes(&data);

  void *bytes;
  _videoFrame->GetBytes(&bytes);
  memcpy(bytes, data, 1920 * 1080 * 4);

  // return _videoConverter->ConvertFrame(videoFrame, _videoFrame);
  return S_OK;
}
