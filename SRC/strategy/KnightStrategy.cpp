#include "strategy/KnightStrategy.h"
#include "model/Board.h"
#include "model/Piece.h"

namespace {
  inline bool inBounds(int f, int r) {
    return f >= 0 && f < 8 && r >= 0 && r < 8;
  }
}

bool KnightStrategy::isLegal(const Board& board,
  int fx, int fr,
  int tx, int tr,
  PieceColor color) const
{
  if (!inBounds(fx, fr) || !inBounds(tx, tr)) return false;

  const int df = tx - fx;
  const int dr = tr - fr;

  // Knight moves in L-shape: 2 squares in one direction, 1 square perpendicular
  const bool validLShape = (abs(df) == 2 && abs(dr) == 1) || (abs(df) == 1 && abs(dr) == 2);
  if (!validLShape) return false;

  const Piece* dst = board.getPiece(tx, tr);

  // Can't capture own piece
  if (dst && dst->getColor() == color) return false;

  return true;
}
