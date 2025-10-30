#pragma once
#include <memory>
#include <array>
#include "model/Piece.h"

class Board {
public:
  Board();

  const Piece* getPiece(int file, int rank) const;
  bool tryMove(int fx, int fr, int tx, int tr);

private:
  std::array<std::array<std::unique_ptr<Piece>, 8>, 8> squares_;

  static bool inBounds(int f, int r) {
    return f >= 0 && f < 8 && r >= 0 && r < 8;
  }
};