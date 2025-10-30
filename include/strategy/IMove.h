#pragma once

class Board;
enum class PieceColor;

// Strategy interface for movement rules
class IMove {
public:
  virtual ~IMove() = default;

  virtual bool isLegal(const Board& board,
    int fx, int fr,
    int tx, int tr,
    PieceColor color) const = 0;
};