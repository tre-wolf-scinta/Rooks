#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <utility>
#include "patterns/IObserver.h"
#include "model/Board.h"

class VisualView : public IObserver {
public:
  explicit VisualView(Board& board, unsigned tileSize = 80);

  void update() override {} // (hook for model changes later)
  void draw(sf::RenderWindow& window);

  void moveCursor(int dFile, int dRank);
  std::pair<int, int> getCursor() const { return { cursorFile_, cursorRank_ }; }

  // Selection control (Space toggles this in main.cpp)
  void setSelected(std::optional<std::pair<int, int>> sel) { selected_ = std::move(sel); }
  void clearSelected() { selected_.reset(); }

  static bool isDarkSquare(int file, int rank) { return ((file + rank) % 2) == 1; }

private:
  void drawBoard(sf::RenderWindow& window);
  void drawPieces(sf::RenderWindow& window);
  void drawCursor(sf::RenderWindow& window);
  void drawSelection(sf::RenderWindow& window); 

  Board& board_;
  unsigned tileSize_;
  int cursorFile_{ 0 };
  int cursorRank_{ 0 };

  bool fontLoaded_{ false };
  sf::Font font_;

  std::optional<std::pair<int, int>> selected_; 
};