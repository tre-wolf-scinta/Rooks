#include <SFML/Graphics.hpp>
#include "model/Board.h"

int main() {
  Board gameBoard;      // Not used yet - testing compilation only
    // SFML 3: make a VideoMode with (size, bitsPerPixel), then window(title, style)
    sf::RenderWindow window(
        sf::VideoMode({400u, 400u}, 32u),
        "Rooks – smoke test",
        sf::Style::Default
    );

    sf::Clock clock;

    while (window.isOpen()) {
        // SFML 3: pollEvent returns std::optional<sf::Event>
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        // draw nothing yet
        window.display();

        if (clock.getElapsedTime().asSeconds() > 1.0f) {
            window.close();
        }
    }
    return 0;
}
