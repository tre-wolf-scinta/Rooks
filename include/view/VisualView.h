#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>   // std::clamp
#include <utility>     // std::pair
#include "patterns/IObserver.h"
#include "model/Board.h"

// Minimal visual view: draws an 8x8 chessboard (black/white) and a cursor outline.
class VisualView : public IObserver {
public:
  explicit VisualView(Board& board, unsigned tileSize = 80)
    : board_(board), tileSize_(tileSize)
  {
    cursorFile_ = 0;  // file a
    cursorRank_ = 0;  // rank 1
  }

  void update() override
  {
    /* Intentionally blank for now */
  }

  void draw(sf::RenderWindow& window) {
    // Draw board: (file 0..7 left->right), (rank 0..7 bottom->top)
    for (int rank = 0; rank < 8; ++rank) {
      for (int file = 0; file < 8; ++file) {
        sf::RectangleShape sq(
          sf::Vector2f(static_cast<float>(tileSize_),
            static_cast<float>(tileSize_)));

        const float x = static_cast<float>(file * static_cast<int>(tileSize_));
        const float y = static_cast<float>((7 - rank) * static_cast<int>(tileSize_));
        sq.setPosition(sf::Vector2f(x, y));

        const bool dark = ((file + rank) % 2) == 1;
        sq.setFillColor(dark ? sf::Color::Black : sf::Color::White);
        window.draw(sq);
      }
    }

    // Cursor outline (red for low-vision accessibility)
    sf::RectangleShape cursor(
      sf::Vector2f(static_cast<float>(tileSize_),
        static_cast<float>(tileSize_)));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineThickness(3.f);
    cursor.setOutlineColor(sf::Color::Red);

    const float cx = static_cast<float>(cursorFile_ * static_cast<int>(tileSize_));
    const float cy = static_cast<float>((7 - cursorRank_) * static_cast<int>(tileSize_));
    cursor.setPosition(sf::Vector2f(cx, cy));
    window.draw(cursor);
  }

  void moveCursor(int dFile, int dRank) {
    cursorFile_ = std::clamp(cursorFile_ + dFile, 0, 7);
    cursorRank_ = std::clamp(cursorRank_ + dRank, 0, 7);
  }

  std::pair<int, int> getCursor() const {
    return { cursorFile_, cursorRank_ };
  }

  static bool isDarkSquare(int file, int rank) {
    return Board::colorAt(file, rank) == SquareColor::Black;
  }
private:
  Board& board_;
  unsigned tileSize_;
  int      cursorFile_{ 0 }; // 0..7
  int      cursorRank_{ 0 }; // 0..7
};
