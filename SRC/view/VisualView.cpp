#include "view/VisualView.h"
#include <filesystem>

VisualView::VisualView(Board& board, unsigned tileSize)
  : board_(board), tileSize_(tileSize)
{
  cursorFile_ = 0;  // a-file
  cursorRank_ = 0;  // rank 1
  fontLoaded_ = loadDefaultFont(); // best-effort; drawPieces() checks this
}

bool VisualView::loadDefaultFont() {
  // On Windows, Arial is available by default
  const std::filesystem::path arial{ R"(C:\Windows\Fonts\arial.ttf)" };
  return font_.openFromFile(arial);
}

void VisualView::draw(sf::RenderWindow& window) {
  drawBoard(window);
  drawPieces(window);
  drawCursor(window);
}

void VisualView::drawBoard(sf::RenderWindow& window) {
  for (int rank = 0; rank < 8; ++rank) {
    for (int file = 0; file < 8; ++file) {
      sf::RectangleShape sq(
        sf::Vector2f(static_cast<float>(tileSize_), static_cast<float>(tileSize_)));

      const float x = static_cast<float>(file * static_cast<int>(tileSize_));
      const float y = static_cast<float>((7 - rank) * static_cast<int>(tileSize_));
      sq.setPosition(sf::Vector2f(x, y));

      const bool dark = ((file + rank) % 2) == 1;
      sq.setFillColor(dark ? sf::Color::Black : sf::Color::White);
      window.draw(sq);
    }
  }
}

void VisualView::drawCursor(sf::RenderWindow& window) {
  sf::RectangleShape cursor(
    sf::Vector2f(static_cast<float>(tileSize_), static_cast<float>(tileSize_)));
  cursor.setFillColor(sf::Color::Transparent);
  cursor.setOutlineThickness(3.f);
  cursor.setOutlineColor(sf::Color::Red);

  const float cx = static_cast<float>(cursorFile_ * static_cast<int>(tileSize_));
  const float cy = static_cast<float>((7 - cursorRank_) * static_cast<int>(tileSize_));
  cursor.setPosition(sf::Vector2f(cx, cy));
  window.draw(cursor);
}

void VisualView::drawPieces(sf::RenderWindow& window) {
  if (!fontLoaded_) return; // fail gracefully if font missing

  const float cell = static_cast<float>(tileSize_);
  const unsigned characterSize = static_cast<unsigned>(cell * 0.6f);

  for (int rank = 0; rank < 8; ++rank) {
    for (int file = 0; file < 8; ++file) {
      const Piece* p = board_.getPiece(file, rank);
      if (!p) continue;

      sf::Text text(font_, p->getSymbol(), characterSize);

      // Contrastful letter colors
      if (p->getColor() == PieceColor::White) {
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color(30, 30, 30));
      }
      else {
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color(225, 225, 225));
      }
      text.setOutlineThickness(2.f);

      // Target square center
      const float x = static_cast<float>(file * static_cast<int>(tileSize_));
      const float y = static_cast<float>((7 - rank) * static_cast<int>(tileSize_));
      const float cx = x + cell / 2.f;
      const float cy = y + cell / 2.f;

      const sf::FloatRect bounds = text.getLocalBounds();
      const sf::Vector2f bpos = bounds.position;
      const sf::Vector2f bsize = bounds.size;

      // Center the glyph in the square
      text.setOrigin(sf::Vector2f(bpos.x + bsize.x / 2.f,
        bpos.y + bsize.y / 2.f));
      text.setPosition(sf::Vector2f(cx, cy));

      window.draw(text);
    }
  }
}
