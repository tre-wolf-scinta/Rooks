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
    resetToStartingPosition();
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

  // Clears all pieces, then places standard chess starting position.
  void resetToStartingPosition() {
    clear();

    // White pawns on rank 1 (row index 1)
    for (int f = 0; f < SIZE; ++f) {
      squares_[1][f] = std::make_unique<Piece>(PieceColor::White, PieceType::Pawn);
    }
    // Black pawns on rank 6 (row index 6)
    for (int f = 0; f < SIZE; ++f) {
      squares_[6][f] = std::make_unique<Piece>(PieceColor::Black, PieceType::Pawn);
    }

    // White back rank (rank 0): R N B Q K B N R
    squares_[0][0] = std::make_unique<Piece>(PieceColor::White, PieceType::Rook);
    squares_[0][1] = std::make_unique<Piece>(PieceColor::White, PieceType::Knight);
    squares_[0][2] = std::make_unique<Piece>(PieceColor::White, PieceType::Bishop);
    squares_[0][3] = std::make_unique<Piece>(PieceColor::White, PieceType::Queen);
    squares_[0][4] = std::make_unique<Piece>(PieceColor::White, PieceType::King);
    squares_[0][5] = std::make_unique<Piece>(PieceColor::White, PieceType::Bishop);
    squares_[0][6] = std::make_unique<Piece>(PieceColor::White, PieceType::Knight);
    squares_[0][7] = std::make_unique<Piece>(PieceColor::White, PieceType::Rook);

    // Black back rank (rank 7): R N B Q K B N R
    squares_[7][0] = std::make_unique<Piece>(PieceColor::Black, PieceType::Rook);
    squares_[7][1] = std::make_unique<Piece>(PieceColor::Black, PieceType::Knight);
    squares_[7][2] = std::make_unique<Piece>(PieceColor::Black, PieceType::Bishop);
    squares_[7][3] = std::make_unique<Piece>(PieceColor::Black, PieceType::Queen);
    squares_[7][4] = std::make_unique<Piece>(PieceColor::Black, PieceType::King);
    squares_[7][5] = std::make_unique<Piece>(PieceColor::Black, PieceType::Bishop);
    squares_[7][6] = std::make_unique<Piece>(PieceColor::Black, PieceType::Knight);
    squares_[7][7] = std::make_unique<Piece>(PieceColor::Black, PieceType::Rook);

    // Notify views if needed later
    // notifyAll();  // (leave commented until you have observers listening for full redraw)
  }

  // Optional: clear the board to all empty squares
  void clear() {
    for (auto& row : squares_) {
      for (auto& cell : row) {
        cell.reset();
      }
    }
  }

  void pingChange() { notifyAll(); }

private:
  // squares_[rank][file] — rank 0 is bottom (white home rank), rank 7 is top
  std::array<std::array<std::unique_ptr<Piece>, SIZE>, SIZE> squares_{};
};
