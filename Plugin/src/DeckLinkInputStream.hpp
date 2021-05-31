#pragma once

#include <DeckLinkAPI.h>

class DeckLinkInputStream : public IDeckLinkInputCallback {
public:
  explicit DeckLinkInputStream(IDeckLink *device);
  virtual ~DeckLinkInputStream() override;

  void Start();
  void Stop();

protected:
  void Run();

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  virtual HRESULT VideoInputFormatChanged(
      /* in */ BMDVideoInputFormatChangedEvents notificationEvents,
      /* in */ IDeckLinkDisplayMode *newDisplayMode,
      /* in */ BMDDetectedVideoInputFormatFlags detectedSignalFlags) override;

  virtual HRESULT VideoInputFrameArrived(
      /* in */ IDeckLinkVideoInputFrame *videoFrame,
      /* in */ IDeckLinkAudioInputPacket *audioPacket) override;

private:
  IDeckLinkInput *_input = nullptr;
};
