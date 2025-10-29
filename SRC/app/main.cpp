#include <SFML/Graphics.hpp>
#include <string>
#include "model/Board.h"
#include "view/Announcer.h"
#include "view/VisualView.h"

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

  // Announce when the game/board is ready
  announcer.speak(L"Game started.");

  bool running = true;
  while (running && window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        running = false;
        window.close();
      }
      if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
        bool moved = false;
        switch (key->scancode) {
        case sf::Keyboard::Scancode::Left:  view.moveCursor(-1, 0); moved = true; break;
        case sf::Keyboard::Scancode::Right: view.moveCursor(+1, 0); moved = true; break;
        case sf::Keyboard::Scancode::Up:    view.moveCursor(0, +1); moved = true; break;
        case sf::Keyboard::Scancode::Down:  view.moveCursor(0, -1); moved = true; break;
        case sf::Keyboard::Scancode::Escape:
          running = false; window.close(); break;
        default: break;
        }
        if (moved) {
          auto [f, r] = view.getCursor();
          const bool dark = VisualView::isDarkSquare(f, r);
          const std::wstring msg = dark ? L"Black square" : L"White square";
          announcer.speak(msg);
        }
      }
    }

    window.clear();
    view.draw(window);
    window.display();
  }

  return 0;
}