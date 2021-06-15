#pragma once

#include <DeckLinkAPI.h>
#include <atomic>
#include <mutex>
#include <vector>

class DeckLinkManager {
public:
  static DeckLinkManager *GetInstance();

  const std::vector<IDeckLink *> *GetDevices() const;

protected:
  std::vector<IDeckLink *> ListDevices() const;

private:
  DeckLinkManager();
  ~DeckLinkManager() = default;
  DeckLinkManager(const DeckLinkManager &) = delete;
  DeckLinkManager(const DeckLinkManager &&) = delete;
  DeckLinkManager &operator=(const DeckLinkManager &) = delete;
  DeckLinkManager &operator=(const DeckLinkManager &&) = delete;

  std::vector<IDeckLink *> _devices;
};
