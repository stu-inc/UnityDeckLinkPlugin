#pragma once

extern "C" int DeckLink_Test() { return 123; }

class DeckLinkManager {
public:
  DeckLinkManager();
  ~DeckLinkManager();

  static int test() { return 5; }
};
