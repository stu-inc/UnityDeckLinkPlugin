#pragma once

#include <DeckLinkAPI.h>
#include <atomic>
#include <mutex>
#include <vector>

class DeckLinkOutputStream : public IDeckLinkVideoOutputCallback {
public:
  explicit DeckLinkOutputStream(IDeckLink *device);

  virtual HRESULT QueryInterface(REFIID iid, LPVOID *ppv) override;
  virtual ULONG AddRef() override;
  virtual ULONG Release() override;

  void AddVideoFrame(IDeckLinkVideoFrame *frame);

  void Start();
  void Stop();

protected:
  virtual ~DeckLinkOutputStream();

  virtual HRESULT ScheduledFrameCompleted(
      /* in */ IDeckLinkVideoFrame *completedFrame,
      /* in */ BMDOutputFrameCompletionResult result) override;

  virtual HRESULT ScheduledPlaybackHasStopped() override;

private:
  std::atomic<ULONG> _counter = 1;
  std::mutex _mutex;
  IDeckLink *_device = nullptr;
  IDeckLinkOutput *_output = nullptr;
  std::vector<IDeckLinkVideoFrame *> _videoFrames;
};
