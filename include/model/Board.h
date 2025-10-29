#pragma once
#include <array>
#include <memory>
#include "patterns/Observer.h"
#include "model/Piece.h"

enum class SquareColor { White, Black };

class Board : public ISubject {
public:
  static constexpr int SIZE = 8;

  Board() {
    // Simple test setup: just rooks and pawns for each side
    for (int file = 0; file < SIZE; ++file) {
      squares_[1][file] = std::make_unique<Piece>(PieceColor::White, PieceType::Pawn);
      squares_[6][file] = std::make_unique<Piece>(PieceColor::Black, PieceType::Pawn);
    }
    squares_[0][0] = std::make_unique<Piece>(PieceColor::White, PieceType::Rook);
    squares_[0][7] = std::make_unique<Piece>(PieceColor::White, PieceType::Rook);
    squares_[7][0] = std::make_unique<Piece>(PieceColor::Black, PieceType::Rook);
    squares_[7][7] = std::make_unique<Piece>(PieceColor::Black, PieceType::Rook);
  }

  static bool inBounds(int file, int rank) {
    return file >= 0 && file < SIZE && rank >= 0 && rank < SIZE;
  }

  static SquareColor colorAt(int file, int rank) {
    const bool dark = ((file + rank) % 2) == 1;
    return dark ? SquareColor::Black : SquareColor::White;
  }

  const Piece* getPiece(int file, int rank) const {
    if (!inBounds(file, rank)) return nullptr;
    return squares_[rank][file].get();
  }

  void pingChange() { notifyAll(); }

private:
  std::array<std::array<std::unique_ptr<Piece>, SIZE>, SIZE> squares_;
};
