#include <SFML/Graphics.hpp>
#include <string>
#include "model/Board.h"
#include "view/Announcer.h"
#include "view/VisualView.h"
#include "controller/InputController.h"   

int main() {
  sf::RenderWindow window(
    sf::VideoMode({ 640u, 640u }, 32u),
    "Rooks",
    sf::Style::Default
  );
  window.setVerticalSyncEnabled(true);

  Board board;
  Announcer announcer(board);
  VisualView view(board, 80);

  announcer.speak(L"Game started.");
  InputController input(board, view, announcer, window, tileSize);

  bool running = true;
  while (running && window.isOpen()) {
    while (auto event = window.pollEvent()) {
      input.handleEvent(*event, running);
    }

    window.clear();
    view.draw(window);
    window.display();
  }

  return 0;
}
