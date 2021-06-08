#pragma once

#include <DeckLinkAPI.h>
#include <atomic>

class DeckLinkVideoFrame;

class DeckLinkInputStream : public IDeckLinkInputCallback {
public:
  explicit DeckLinkInputStream(IDeckLink *device);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void Start();
  void Stop();

  IDeckLinkVideoFrame *VideoFrame();

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
  DeckLinkVideoFrame *_videoFrame = nullptr;
  IDeckLinkVideoConversion *_videoConverter = nullptr;
};
