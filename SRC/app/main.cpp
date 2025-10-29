#include <SFML/Graphics.hpp>
#include <string>
#include "model/Board.h"
#include "view/Announcer.h"
#include "view/VisualView.h"

// Convert (file, rank) -> "A1" .. "H8"
static std::wstring toAlgebraic(int file, int rank) {
  wchar_t f = static_cast<wchar_t>(L'A' + file);
  wchar_t r = static_cast<wchar_t>(L'1' + rank);
  std::wstring out;
  out.push_back(f);
  out.push_back(r);
  return out;
}

// Human-friendly piece name: "White Pawn", "Black Rook", etc.
static std::wstring pieceFullName(const Piece& p) {
  const wchar_t* color = (p.getColor() == PieceColor::White) ? L"White" : L"Black";
  const wchar_t* type = L"?";
  switch (p.getType()) {
  case PieceType::Pawn:   type = L"Pawn";   break;
  case PieceType::Rook:   type = L"Rook";   break;
  case PieceType::Knight: type = L"Knight"; break;
  case PieceType::Bishop: type = L"Bishop"; break;
  case PieceType::Queen:  type = L"Queen";  break;
  case PieceType::King:   type = L"King";   break;
  }
  return std::wstring(color) + L" " + type;
}
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
          running = false;
          window.close();
          break;
        default:
          break;
        }

        if (moved) {
          auto [f, r] = view.getCursor();

          const bool dark = VisualView::isDarkSquare(f, r);
          const wchar_t* colorWord = dark ? L"Black" : L"White";
          const std::wstring coord = toAlgebraic(f, r);

          // Look up piece on this square
          const Piece* piece = board.getPiece(f, r);

          if (piece) {
            // Example: "White E4, occupied by Black Pawn"
            announcer.speak(std::wstring(colorWord) + L" " + coord +
              L", occupied by " + pieceFullName(*piece));
          }
          else {
            // Example: "White E4, empty"
            announcer.speak(std::wstring(colorWord) + L" " + coord + L", empty");
          }
        }

      }
    } 

    window.clear();
    view.draw(window);
    window.display();
  } // ← closes outer while(running && window.isOpen())

  return 0;
}