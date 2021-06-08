#pragma once

#include <DeckLinkAPI.h>
#include <atomic>

class DeckLinkVideoConverter : public IDeckLinkVideoConversion {
public:
  DeckLinkVideoConverter();

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  virtual HRESULT ConvertFrame(/* in */ IDeckLinkVideoFrame *srcFrame,
                               /* in */ IDeckLinkVideoFrame *dstFrame) override;

protected:
  ~DeckLinkVideoConverter();

private:
  std::atomic<ULONG> _counter = 1;
  IDeckLinkVideoConversion *_videoConverter = nullptr;
};
