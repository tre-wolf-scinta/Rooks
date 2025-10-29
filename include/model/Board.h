#pragma once
#include "patterns/Observer.h"

// Files: 0..7 = A..H
// Ranks: 0..7 = 1..8  (rank 0 is bottom, drawn at y = (7 - rank))
enum class SquareColor { White, Black };

class Board : public ISubject {
public:
  Board() = default;

  static bool inBounds(int file, int rank) {
    return file >= 0 && file < 8 && rank >= 0 && rank < 8;
  }

  static SquareColor colorAt(int file, int rank) {
    // odd  => Black
    // even => White
    const bool dark = ((file + rank) % 2) == 1;
    return dark ? SquareColor::Black : SquareColor::White;
  }

  // Placeholder to prove observer flow (already used earlier):
  void pingChange() { notifyAll(); }
};
