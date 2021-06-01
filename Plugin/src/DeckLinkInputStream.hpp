#pragma once

#include <DeckLinkAPI.h>

class DeckLinkInputStream : public IDeckLinkInputCallback {
public:
  explicit DeckLinkInputStream(IDeckLink *device);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void Start();
  void Stop();

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
  IDeckLinkInput *_input = nullptr;
};
