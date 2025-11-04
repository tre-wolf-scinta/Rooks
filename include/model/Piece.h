#pragma once
#include <string>
#include <memory>
#include "Strategy/PieceStrategy.h"

enum class PieceColor { White, Black };
enum class PieceType { King, Queen, Rook, Bishop, Knight, Pawn };

class Piece {
public:
  Piece(PieceColor color, PieceType type)
    : color_(color), type_(type)
  {
    switch (type_) {
    case PieceType::Pawn:
      strategy_ = std::make_unique<PawnStrategy>();
      break;
    case PieceType::Knight:
      strategy_ = std::make_unique<KnightStrategy>();
      break;
    case PieceType::Bishop:
      strategy_ = std::make_unique<BishopStrategy>();
      break;
    case PieceType::Rook:
      strategy_ = std::make_unique<RookStrategy>();
      break;
    case PieceType::Queen:
      strategy_ = std::make_unique<QueenStrategy>();
      break;
    case PieceType::King:
      strategy_ = std::make_unique<KingStrategy>();
      break;
    default:
      strategy_.reset();
      break;
    }
  }

  virtual ~Piece() = default;

  PieceColor getColor() const { return color_; }
  PieceType  getType()  const { return type_; }

  std::wstring getSymbol() const {
    switch (type_) {
    case PieceType::King:   return L"K";
    case PieceType::Queen:  return L"Q";
    case PieceType::Rook:   return L"R";
    case PieceType::Bishop: return L"B";
    case PieceType::Knight: return L"N";
    case PieceType::Pawn:   return L"P";
    }
    return L"?";
  }

  const IMove* getStrategy() const { return strategy_.get(); }

private:
  PieceColor color_;
  PieceType  type_;
  std::unique_ptr<IMove> strategy_;
};