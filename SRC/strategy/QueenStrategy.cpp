#include "strategy/QueenStrategy.h"
#include "model/Board.h"
#include "model/Piece.h"

namespace {
  inline bool inBounds(int f, int r) {
    return f >= 0 && f < 8 && r >= 0 && r < 8;
  }
}

bool QueenStrategy::isLegal(const Board& board,
  int fx, int fr,
  int tx, int tr,
  PieceColor color) const
{
  if (!inBounds(fx, fr) || !inBounds(tx, tr)) return false;

  const int df = tx - fx;
  const int dr = tr - fr;

  // Queen can't stay in place
  if (df == 0 && dr == 0) return false;

  // Queen moves like rook (horizontal/vertical) or bishop (diagonal)
  const bool isRookMove = (df == 0 || dr == 0);
  const bool isBishopMove = (abs(df) == abs(dr));

  if (!isRookMove && !isBishopMove) return false;

  // Check path is clear (no pieces between start and destination)
  const int stepF = (df == 0) ? 0 : ((df > 0) ? 1 : -1);
  const int stepR = (dr == 0) ? 0 : ((dr > 0) ? 1 : -1);

  int f = fx + stepF;
  int r = fr + stepR;

  while (f != tx || r != tr) {
    if (board.getPiece(f, r) != nullptr) return false;
    f += stepF;
    r += stepR;
  }

  const Piece* dst = board.getPiece(tx, tr);

  // Can't capture own piece
  if (dst && dst->getColor() == color) return false;

  return true;
}
