#include "strategy/KingStrategy.h"
#include "model/Board.h"
#include "model/Piece.h"

namespace {
  inline bool inBounds(int f, int r) {
    return f >= 0 && f < 8 && r >= 0 && r < 8;
  }
}

bool KingStrategy::isLegal(const Board& board,
  int fx, int fr,
  int tx, int tr,
  PieceColor color) const
{
  if (!inBounds(fx, fr) || !inBounds(tx, tr)) return false;

  const int df = tx - fx;
  const int dr = tr - fr;

  // King moves exactly one square in any direction
  if (abs(df) > 1 || abs(dr) > 1) return false;

  // King can't stay in place
  if (df == 0 && dr == 0) return false;

  const Piece* dst = board.getPiece(tx, tr);

  // Can't capture own piece
  if (dst && dst->getColor() == color) return false;

  return true;
}
