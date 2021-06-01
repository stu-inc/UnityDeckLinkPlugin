#pragma once

#include <DeckLinkAPI.h>
#include <mutex>

class DeckLinkInputStream : public IDeckLinkInputCallback {
public:
  explicit DeckLinkInputStream(IDeckLink *device);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void Lock();
  void Unlock();

  void Start();
  void Stop();

  IDeckLinkVideoFrame *VideoFrame();

protected:
  virtual ~DeckLinkInputStream() {}

  virtual HRESULT VideoInputFormatChanged(
      /* in */ BMDVideoInputFormatChangedEvents notificationEvents,
      /* in */ IDeckLinkDisplayMode *newDisplayMode,
      /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags) override;

  virtual HRESULT VideoInputFrameArrived(
      /* in */ IDeckLinkVideoInputFrame *videoFrame,
      /* in */ IDeckLinkAudioInputPacket *audioPacket) override;

private:
  int _counter = 0;
  std::mutex _mutex;
  IDeckLinkInput *_input = nullptr;
  IDeckLinkVideoFrame *_videoFrame = nullptr;
};
