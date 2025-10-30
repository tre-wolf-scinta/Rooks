#include "strategy/PawnStrategy.h"
#include "model/Board.h"
#include "model/Piece.h"

namespace {
  inline bool inBounds(int f, int r) {
    return f >= 0 && f < 8 && r >= 0 && r < 8;
  }
}

bool PawnStrategy::isLegal(const Board& board,
  int fx, int fr,
  int tx, int tr,
  PieceColor color) const
{
  if (!inBounds(fx, fr) || !inBounds(tx, tr)) return false;

  const int dir = (color == PieceColor::White) ? +1 : -1;
  const int startRank = (color == PieceColor::White) ? 1 : 6;

  const int df = tx - fx;
  const int dr = tr - fr;

  const Piece* dst = board.getPiece(tx, tr);

  // 1-square forward
  if (df == 0 && dr == dir) {
    return dst == nullptr;
  }

  // 2-square from starting rank (path must be clear)
  if (df == 0 && fr == startRank && dr == 2 * dir) {
    const int midr = fr + dir;
    if (board.getPiece(fx, midr) == nullptr && dst == nullptr) {
      return true;
    }
    return false;
  }

  // Diagonal capture
  if ((df == +1 || df == -1) && dr == dir) {
    if (dst && dst->getColor() != color) {
      return true;
    }
    return false;
  }

  return false;
}