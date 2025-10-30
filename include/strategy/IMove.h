#pragma once
#include "model/Piece.h"    
class Board;                // forward declare to avoid heavy include

class IMove{
public:
  virtual ~IMoveStrategy() = default;

  // Return true if piece of `color` may move from (fx,fr) to (tx,tr) on given board.
  virtual bool isLegal(const Board& board,
    int fx, int fr,
    int tx, int tr,
    PieceColor color) const = 0;
};