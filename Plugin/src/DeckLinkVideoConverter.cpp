#include "DeckLinkVideoConverter.hpp"
#include <algorithm>
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

  // YUV422 to ARGB with BT.601
  if (srcFormat == bmdFormat8BitYUV && dstFormat == bmdFormat8BitARGB) {

    for (long i = 0; i < srcHeight; ++i) {

      auto p_src = srcBytes + srcRowBytes * i;
      auto p_dst = dstBytes + dstRowBytes * (dstHeight - (i + 1));

      for (long j = 0; j < srcWidth / 2; ++j) {

        auto y1 = *(p_src + 1) - 16;
        auto y2 = *(p_src + 3) - 16;
        auto cr = *(p_src + 2) - 128;
        auto cb = *(p_src + 0) - 128;

        int r1 = (298 * y1 + 409 * cr) >> 8;
        int g1 = (298 * y1 - 100 * cb - 208 * cr) >> 8;
        int b1 = (298 * y1 + 516 * cb) >> 8;

        int r2 = (298 * y2 + 409 * cr) >> 8;
        int g2 = (298 * y2 - 100 * cb - 208 * cr) >> 8;
        int b2 = (298 * y2 + 516 * cb) >> 8;

        p_dst[1] = std::clamp(r1, 0, 255);
        p_dst[2] = std::clamp(g1, 0, 255);
        p_dst[3] = std::clamp(b1, 0, 255);
        p_dst[0] = 255;

        p_dst[5] = std::clamp(r2, 0, 255);
        p_dst[6] = std::clamp(g2, 0, 255);
        p_dst[7] = std::clamp(b2, 0, 255);
        p_dst[4] = 255;

        p_src += 4;
        p_dst += 8;
      }
    }

    return S_OK;
  }

  return E_NOTIMPL;
}
