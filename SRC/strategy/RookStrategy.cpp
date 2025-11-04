#include "strategy/RookStrategy.h"
#include "model/Board.h"
#include "model/Piece.h"

namespace {
  inline bool inBounds(int f, int r) {
    return f >= 0 && f < 8 && r >= 0 && r < 8;
  }
}

bool RookStrategy::isLegal(const Board& board,
  int fx, int fr,
  int tx, int tr,
  PieceColor color) const
{
  if (!inBounds(fx, fr) || !inBounds(tx, tr)) return false;

  const int df = tx - fx;
  const int dr = tr - fr;

  // Rook moves horizontally or vertically (but not both)
  if ((df != 0 && dr != 0) || (df == 0 && dr == 0)) return false;

  // Check path is clear (no pieces between start and destination)
  if (df != 0) {
    // Horizontal movement
    const int stepF = (df > 0) ? 1 : -1;
    for (int f = fx + stepF; f != tx; f += stepF) {
      if (board.getPiece(f, fr) != nullptr) return false;
    }
  } else {
    // Vertical movement
    const int stepR = (dr > 0) ? 1 : -1;
    for (int r = fr + stepR; r != tr; r += stepR) {
      if (board.getPiece(fx, r) != nullptr) return false;
    }
  }

  const Piece* dst = board.getPiece(tx, tr);

  // Can't capture own piece
  if (dst && dst->getColor() == color) return false;

  return true;
}
