#pragma once
#include "strategy/IMove.h"

class RookStrategy final : public IMove {
public:
  bool isLegal(const Board& board,
    int fx, int fr,
    int tx, int tr,
    PieceColor color) const override;
};
