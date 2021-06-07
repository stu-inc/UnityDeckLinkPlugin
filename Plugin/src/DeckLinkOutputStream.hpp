#pragma once

#include <DeckLinkAPI.h>
#include <atomic>
#include <mutex>

class DeckLinkOutputStream : public IDeckLinkVideoOutputCallback {
public:
  explicit DeckLinkOutputStream(IDeckLink *device);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void Lock();
  void Unlock();

  void Start();
  void Stop();

protected:
  virtual ~DeckLinkOutputStream();

  virtual HRESULT ScheduledFrameCompleted(
      /* in */ IDeckLinkVideoFrame *completedFrame,
      /* in */ BMDOutputFrameCompletionResult result) override;

  virtual HRESULT ScheduledPlaybackHasStopped(void) override;

private:
  std::atomic<ULONG> _counter = 0;
  std::mutex _mutex;
  IDeckLinkOutput *_output = nullptr;
  IDeckLinkMutableVideoFrame *_videoFrame = nullptr;
};
