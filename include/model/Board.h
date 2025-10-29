#pragma once
#include "patterns/Observer.h"

class Board : public ISubject {
public:
  Board() = default;

  void updateObservers() {
    notifyAll();
  }
};