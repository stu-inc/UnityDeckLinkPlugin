#pragma once

#include <DeckLinkAPI.h>
#include <atomic>

class DeckLinkVideoFrame;
class DeckLinkVideoConverter;

class DeckLinkInputStream : public IDeckLinkInputCallback {
public:
  explicit DeckLinkInputStream(IDeckLink *device);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void Start();
  void Stop();

  BMDTimeValue GetTimeStamp() const;

  IDeckLinkVideoFrame *GetVideoFrame() const;

  BMDPixelFormat GetPixelFormat() const;
  void SetPixelFormat(BMDPixelFormat pixelFormat);

protected:
  virtual ~DeckLinkInputStream();

  virtual HRESULT VideoInputFormatChanged(
      /* in */ BMDVideoInputFormatChangedEvents notificationEvents,
      /* in */ IDeckLinkDisplayMode *newDisplayMode,
      /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags) override;

  virtual HRESULT VideoInputFrameArrived(
      /* in */ IDeckLinkVideoInputFrame *videoFrame,
      /* in */ IDeckLinkAudioInputPacket *audioPacket) override;

private:
  std::atomic<ULONG> _counter = 1;
  IDeckLink *_device = nullptr;
  IDeckLinkInput *_input = nullptr;
  BMDPixelFormat _pixelFormat = bmdFormat8BitYUV;
  BMDDisplayMode _displayMode = bmdModeHD1080p5994;
  DeckLinkVideoFrame *_videoFrame = nullptr;
  DeckLinkVideoConverter *_videoConverter = nullptr;
  BMDTimeValue _timeStamp = 0;
};
