// Header for handling user input events and transient UI state using SFML. 
// Implementation in InputController.cpp. 

#pragma once
#include <SFML/Window/Event.hpp>  
#include <optional>
#include <utility>                 

// Forward declarations  
namespace sf { class RenderWindow; }
class Board;
class VisualView;
class Announcer;

class InputController {
public:
  InputController(Board& board,
    VisualView& view,
    Announcer& announcer,
    sf::RenderWindow& window,
    unsigned tileSize);

// Called for every SFML event
  void handleEvent(const sf::Event& ev, bool& running);

private:
// Event handlers 
  void handleMouseButtonPressed(const sf::Event::MouseButtonPressed& mb);
  void handleKeyPressed(const sf::Event::KeyPressed& key, bool& running);

// Helpers that depend on window/tile size
  std::optional<std::pair<int, int>> mouseToBoard();
  void announceCursorSquare();
  void tryMoveSelectedTo(int file, int rank);
  void clearSelection();

private:
  Board& board_;
  VisualView& view_;
  Announcer& announcer_;
  sf::RenderWindow& window_;
  unsigned tileSize_ = 80;

  // Transient UI state 
  std::optional<std::pair<int, int>> selected_;
};