#pragma once
#include <string>
#include <Windows.h>
#include <sapi.h>
#include <wrl/client.h>

#include "patterns/IObserver.h"
#include "model/Board.h"

class Announcer : public IObserver {
public:
  explicit Announcer(Board& board);
  ~Announcer() override;

  void update() override;
  void speak(const std::wstring& msg);

private:
  Board& board_;
  Microsoft::WRL::ComPtr<ISpVoice> voice_;

  bool initVoice();
  void cleanupVoice();
};