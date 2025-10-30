#include "model/Board.h"

Board::Board() {
  for (int r = 0; r < 8; ++r)
    for (int f = 0; f < 8; ++f)
      squares_[r][f].reset();

  // Pawns
  for (int f = 0; f < 8; ++f) {
    squares_[1][f] = std::make_unique<Piece>(PieceColor::White, PieceType::Pawn);
    squares_[6][f] = std::make_unique<Piece>(PieceColor::Black, PieceType::Pawn);
  }

  // White back rank
  squares_[0][0] = std::make_unique<Piece>(PieceColor::White, PieceType::Rook);
  squares_[0][1] = std::make_unique<Piece>(PieceColor::White, PieceType::Knight);
  squares_[0][2] = std::make_unique<Piece>(PieceColor::White, PieceType::Bishop);
  squares_[0][3] = std::make_unique<Piece>(PieceColor::White, PieceType::Queen);
  squares_[0][4] = std::make_unique<Piece>(PieceColor::White, PieceType::King);
  squares_[0][5] = std::make_unique<Piece>(PieceColor::White, PieceType::Bishop);
  squares_[0][6] = std::make_unique<Piece>(PieceColor::White, PieceType::Knight);
  squares_[0][7] = std::make_unique<Piece>(PieceColor::White, PieceType::Rook);

  // Black back rank
  squares_[7][0] = std::make_unique<Piece>(PieceColor::Black, PieceType::Rook);
  squares_[7][1] = std::make_unique<Piece>(PieceColor::Black, PieceType::Knight);
  squares_[7][2] = std::make_unique<Piece>(PieceColor::Black, PieceType::Bishop);
  squares_[7][3] = std::make_unique<Piece>(PieceColor::Black, PieceType::Queen);
  squares_[7][4] = std::make_unique<Piece>(PieceColor::Black, PieceType::King);
  squares_[7][5] = std::make_unique<Piece>(PieceColor::Black, PieceType::Bishop);
  squares_[7][6] = std::make_unique<Piece>(PieceColor::Black, PieceType::Knight);
  squares_[7][7] = std::make_unique<Piece>(PieceColor::Black, PieceType::Rook);
}

const Piece* Board::getPiece(int file, int rank) const {
  if (!inBounds(file, rank)) return nullptr;
  return squares_[rank][file].get();
}

bool Board::tryMove(int fx, int fr, int tx, int tr) {
  if (!inBounds(fx, fr) || !inBounds(tx, tr)) return false;

  std::unique_ptr<Piece>& src = squares_[fr][fx];
  if (!src) return false;

  const IMove* strat = src->getStrategy();
  if (!strat) return false;

  if (!strat->isLegal(*this, fx, fr, tx, tr, src->getColor()))
    return false;

  // capture (if any) and move
  squares_[tr][tx] = std::move(src);
  return true;
}