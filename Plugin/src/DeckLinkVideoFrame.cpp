#include "DeckLinkVideoFrame.hpp"

static long pixelFormatToBytes(BMDPixelFormat format) {

  if (format == bmdFormat8BitARGB) {
    return 4;
  } else if (format == bmdFormat8BitBGRA) {
    return 4;
  }

  return 0;
}

DeckLinkVideoFrame::DeckLinkVideoFrame(long width, long height,
                                       BMDPixelFormat format)
    : IDeckLinkVideoFrame() {

  // Resize
  Resize(width, height, format);
}

DeckLinkVideoFrame::~DeckLinkVideoFrame() {}

HRESULT DeckLinkVideoFrame::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkVideoFrame::AddRef() { return ++_counter; }

ULONG DeckLinkVideoFrame::Release() {

  if (!--_counter) {
    delete this;
    return 0;
  }

  return _counter;
}

void DeckLinkVideoFrame::Resize(long width, long height,
                                BMDPixelFormat format) {

  // Set properties
  _width = width;
  _height = height;
  _rowBytes = width * pixelFormatToBytes(format);
  _pixelFormat = format;

  // Allocate memory
  auto size = _height * _rowBytes;

  _data.reserve(size);
  _data.resize(size);
}

HRESULT DeckLinkVideoFrame::GetBytes(void **buffer) {
  *buffer = (void *)_data.data();
  return S_OK;
}

HRESULT
DeckLinkVideoFrame::GetTimecode(BMDTimecodeFormat format,
                                IDeckLinkTimecode **timecode) {
  return E_NOINTERFACE;
}

HRESULT
DeckLinkVideoFrame::GetAncillaryData(IDeckLinkVideoFrameAncillary **ancillary) {
  return E_NOINTERFACE;
}
