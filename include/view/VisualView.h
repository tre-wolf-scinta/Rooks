#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>   // std::clamp
#include <utility>     // std::pair
#include <string>
#include "patterns/IObserver.h"
#include "model/Board.h"
#include "model/Piece.h"

// VisualView: draws an 8x8 chessboard (black/white), a cursor outline, and piece letters.
class VisualView : public IObserver {
public:
  explicit VisualView(Board& board, unsigned tileSize = 80);

  void update() override { /* no-op for now */ }

  void draw(sf::RenderWindow& window);

  void moveCursor(int dFile, int dRank) {
    cursorFile_ = std::clamp(cursorFile_ + dFile, 0, 7);
    cursorRank_ = std::clamp(cursorRank_ + dRank, 0, 7);
  }

  std::pair<int, int> getCursor() const { return { cursorFile_, cursorRank_ }; }

  static bool isDarkSquare(int file, int rank) {
    return Board::colorAt(file, rank) == SquareColor::Black;
  }

private:
  void drawBoard(sf::RenderWindow& window);
  void drawCursor(sf::RenderWindow& window);
  void drawPieces(sf::RenderWindow& window);
  bool loadDefaultFont();

  Board& board_;
  unsigned tileSize_;
  int      cursorFile_{ 0 }; // 0..7
  int      cursorRank_{ 0 }; // 0..7
  sf::Font font_;
  bool     fontLoaded_{ false };
};
