#pragma once

#include <DeckLinkAPI.h>
#include <atomic>
#include <mutex>
#include <vector>

class DeckLinkVideoFrame : public IDeckLinkVideoFrame {
public:
  DeckLinkVideoFrame(long width, long height, BMDPixelFormat format);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void Resize(long width, long height, BMDPixelFormat format);

  virtual long GetWidth(void) override { return _width; }
  virtual long GetHeight(void) override { return _height; }
  virtual long GetRowBytes(void) override { return _rowBytes; }
  virtual BMDPixelFormat GetPixelFormat(void) override { return _pixelFormat; }
  virtual BMDFrameFlags GetFlags(void) override { return bmdFrameFlagDefault; };
  virtual HRESULT GetBytes(/* out */ void **buffer) override;
  virtual HRESULT GetTimecode(/* in */ BMDTimecodeFormat format,
                              /* out */ IDeckLinkTimecode **timecode) override;
  virtual HRESULT GetAncillaryData(
      /* out */ IDeckLinkVideoFrameAncillary **ancillary) override;

protected:
  ~DeckLinkVideoFrame();

private:
  std::atomic<ULONG> _counter = 0;
  std::mutex _mutex;

  long _width = 0;
  long _height = 0;
  long _rowBytes = 0;
  BMDPixelFormat _pixelFormat = bmdFormatUnspecified;
  std::vector<uint8_t> _data;
};
