#pragma once
#include <string>

enum class PieceColor { White, Black };
enum class PieceType { King, Queen, Rook, Bishop, Knight, Pawn };

class Piece {
public:
  Piece(PieceColor color, PieceType type)
    : color_(color), type_(type) {
  }

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

private:
  PieceColor color_;
  PieceType  type_;
}
;
