#include "DeckLinkVideoConverter.hpp"
#include <string.h>

DeckLinkVideoConverter::DeckLinkVideoConverter() : IDeckLinkVideoConversion() {

  // Create DeckLink video converter
#if defined(WIN32)
  CoCreateInstance(CLSID_CDeckLinkVideoConversion, NULL, CLSCTX_ALL,
                   IID_IDeckLinkVideoConversion, (LPVOID *)&_videoConverter);
#else
  _videoConverter = CreateVideoConversionInstance();
#endif
}

DeckLinkVideoConverter::~DeckLinkVideoConverter() {

  // Release DeckLink video converter
  _videoConverter->Release();
}

HRESULT DeckLinkVideoConverter::QueryInterface(REFIID iid, LPVOID *ppv) {
  return E_NOINTERFACE;
}

ULONG DeckLinkVideoConverter::AddRef() { return ++_counter; }

ULONG DeckLinkVideoConverter::Release() {

  if (!--_counter) {
    delete this;
    return 0;
  }

  return _counter;
}

HRESULT DeckLinkVideoConverter::ConvertFrame(
    /* in */ IDeckLinkVideoFrame *srcFrame,
    /* in */ IDeckLinkVideoFrame *dstFrame) {

  // DeckLink video converter
  if (_videoConverter->ConvertFrame(srcFrame, dstFrame) == S_OK)
    return S_OK;

  // Fallback conversion
  auto srcWidth = srcFrame->GetWidth();
  auto dstWidth = dstFrame->GetWidth();

  auto srcHeight = srcFrame->GetHeight();
  auto dstHeight = dstFrame->GetHeight();

  auto srcRowBytes = srcFrame->GetRowBytes();
  auto dstRowBytes = dstFrame->GetRowBytes();

  auto srcFormat = srcFrame->GetPixelFormat();
  auto dstFormat = dstFrame->GetPixelFormat();

  uint8_t *srcBytes = nullptr;
  uint8_t *dstBytes = nullptr;
  srcFrame->GetBytes((void **)&srcBytes);
  dstFrame->GetBytes((void **)&dstBytes);

  // Size check
  if (srcWidth != dstWidth || srcHeight != dstHeight)
    return E_FAIL;

  // Same format
  if (srcFormat == dstFormat) {
    for (long i = 0; i < srcHeight; ++i) {
      auto p_src = srcBytes + srcRowBytes * i;
      auto p_dst = dstBytes + dstRowBytes * (dstHeight - (i + 1));
      memcpy(p_dst, p_src, srcRowBytes);
    }
    return S_OK;
  }

  return E_NOTIMPL;
}
