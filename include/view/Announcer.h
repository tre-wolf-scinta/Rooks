#pragma once
#include <string>
#include <memory>
#include <Windows.h>
#include <sapi.h>     // SAPI for screenreader-agnostic voice output
#include <wrl/client.h>         // For Microsoft::WRL::ComPtr
#include "patterns/IObserver.h"     // Interface
#include "model/Board.h"      // Board is a subject

// Announcer observes the board and provides voice output via SAPI
class Announcer : public IObserver {
public:
  explicit Announcer(Board& board);      // explicit to disallow implicit Board to Announcer conversions
  ~Announcer() override;

  // Observer callback
  void update() override;

  // Public utility - Called from controller
  void speak(const std::wstring& msg);      // wstring because SAPI expects wide strings

private:
  Board& board_;
  Microsoft::WRL::ComPtr<ISpVoice> voice_;      // COM smart pointer

  // Initialize SAPI voice
  bool initVoice();
};