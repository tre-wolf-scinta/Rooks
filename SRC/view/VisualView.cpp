#include "view/VisualView.h"
#include <filesystem>

VisualView::VisualView(Board& board, unsigned tileSize)
  : board_(board), tileSize_(tileSize) {
  cursorFile_ = 0;
  cursorRank_ = 0;
  // Load Arial (Windows)
  const std::filesystem::path arial{ R"(C:\Windows\Fonts\arial.ttf)" };
  fontLoaded_ = font_.openFromFile(arial);
}

void VisualView::draw(sf::RenderWindow& window) {
  drawBoard(window);
  drawPieces(window);
  drawSelection(window);  
  drawCursor(window);
}

void VisualView::drawBoard(sf::RenderWindow& window) {
  for (int rank = 0; rank < 8; ++rank) {
    for (int file = 0; file < 8; ++file) {
      sf::RectangleShape sq({ static_cast<float>(tileSize_), static_cast<float>(tileSize_) });
      const float x = static_cast<float>(file * static_cast<int>(tileSize_));
      const float y = static_cast<float>((7 - rank) * static_cast<int>(tileSize_));
      sq.setPosition({ x, y });
      sq.setFillColor(((file + rank) % 2) ? sf::Color::Black : sf::Color::White);
      window.draw(sq);
    }
  }
}

void VisualView::drawPieces(sf::RenderWindow& window) {
  if (!fontLoaded_) return;
  const float cell = static_cast<float>(tileSize_);
  const unsigned characterSize = static_cast<unsigned>(cell * 0.6f);

  for (int rank = 0; rank < 8; ++rank) {
    for (int file = 0; file < 8; ++file) {
      const Piece* p = board_.getPiece(file, rank);
      if (!p) continue;

      sf::Text text(font_, p->getSymbol(), characterSize);
      if (p->getColor() == PieceColor::White) {
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color(30, 30, 30));
      }
      else {
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color(225, 225, 225));
      }
      text.setOutlineThickness(2.f);

      const float x = static_cast<float>(file * static_cast<int>(tileSize_));
      const float y = static_cast<float>((7 - rank) * static_cast<int>(tileSize_));
      const float cx = x + cell / 2.f;
      const float cy = y + cell / 2.f;

      const sf::FloatRect bounds = text.getLocalBounds();
      const sf::Vector2f bpos = bounds.position;
      const sf::Vector2f bsize = bounds.size;

      text.setOrigin({ bpos.x + bsize.x / 2.f, bpos.y + bsize.y / 2.f });
      text.setPosition({ cx, cy });
      window.draw(text);
    }
  }
}

void VisualView::drawCursor(sf::RenderWindow& window) {
  sf::RectangleShape cursor({ static_cast<float>(tileSize_), static_cast<float>(tileSize_) });
  cursor.setFillColor(sf::Color::Transparent);
  cursor.setOutlineThickness(3.f);
  cursor.setOutlineColor(sf::Color::Red);

  const float cx = static_cast<float>(cursorFile_ * static_cast<int>(tileSize_));
  const float cy = static_cast<float>((7 - cursorRank_) * static_cast<int>(tileSize_));
  cursor.setPosition({ cx, cy });
  window.draw(cursor);
}

void VisualView::drawSelection(sf::RenderWindow& window) {
  if (!selected_) return;
  const auto [sfIdx, srIdx] = *selected_;
  sf::RectangleShape sel({ static_cast<float>(tileSize_), static_cast<float>(tileSize_) });
  sel.setFillColor(sf::Color::Transparent);
  sel.setOutlineThickness(4.f);
  sel.setOutlineColor(sf::Color(0, 200, 0)); 
  const float sx = static_cast<float>(sfIdx * static_cast<int>(tileSize_));
  const float sy = static_cast<float>((7 - srIdx) * static_cast<int>(tileSize_));
  sel.setPosition({ sx, sy });
  window.draw(sel);
}

void VisualView::moveCursor(int dFile, int dRank) {
  cursorFile_ = std::clamp(cursorFile_ + dFile, 0, 7);
  cursorRank_ = std::clamp(cursorRank_ + dRank, 0, 7);
}