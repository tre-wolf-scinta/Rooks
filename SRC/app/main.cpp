#include <SFML/Graphics.hpp>
#include <string>
#include <optional>   
#include "model/Board.h"
#include "view/Announcer.h"
#include "view/VisualView.h"

static std::wstring toAlgebraic(int file, int rank) {
  wchar_t f = static_cast<wchar_t>(L'A' + file);
  wchar_t r = static_cast<wchar_t>(L'1' + rank);
  std::wstring out; out.push_back(f); out.push_back(r);
  return out;
}

static const wchar_t* colorWord(PieceColor c) {
  return (c == PieceColor::White) ? L"White" : L"Black";
}
static const wchar_t* pieceWord(PieceType t) {
  switch (t) {
  case PieceType::King:   return L"King";
  case PieceType::Queen:  return L"Queen";
  case PieceType::Rook:   return L"Rook";
  case PieceType::Bishop: return L"Bishop";
  case PieceType::Knight: return L"Knight";
  case PieceType::Pawn:   return L"Pawn";
  }
  return L"Piece";
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

  announcer.speak(L"Game started.");

  // Track selected square, if any
  std::optional<std::pair<int, int>> selected;

  bool running = true;
  while (running && window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        running = false;
        window.close();
      }
      if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
        bool movedCursor = false;

        switch (key->scancode) {
        case sf::Keyboard::Scancode::Left:  view.moveCursor(-1, 0); movedCursor = true; break;
        case sf::Keyboard::Scancode::Right: view.moveCursor(+1, 0); movedCursor = true; break;
        case sf::Keyboard::Scancode::Up:    view.moveCursor(0, +1); movedCursor = true; break;
        case sf::Keyboard::Scancode::Down:  view.moveCursor(0, -1); movedCursor = true; break;

        case sf::Keyboard::Scancode::Escape:
          running = false; window.close(); break;

        case sf::Keyboard::Scancode::Space: {
          auto [f, r] = view.getCursor();
          if (!selected) {
            // Select if there is a piece on the cursor square
            if (const Piece* p = board.getPiece(f, r)) {
              selected = std::make_pair(f, r);
              view.setSelected(selected);
              std::wstring msg = std::wstring(L"Selected ") +
                colorWord(p->getColor()) + L" " +
                pieceWord(p->getType()) + L" at " +
                toAlgebraic(f, r);
              announcer.speak(msg);
            }
            else {
              announcer.speak(L"No piece on this square to select.");
            }
          }
          else {
            // Toggle off selection
            selected.reset();
            view.clearSelected();
            announcer.speak(L"Selection cleared.");
          }
          break;
        }

        case sf::Keyboard::Scancode::Enter: {
          if (selected) {
            auto [sfFile, sfRank] = *selected;
            auto [tfFile, tfRank] = view.getCursor();

            if (sfFile == tfFile && sfRank == tfRank) {
              announcer.speak(L"Cannot drop on the same square.");
              break;
            }

            const Piece* mover = board.getPiece(sfFile, sfRank);
            const Piece* target = board.getPiece(tfFile, tfRank);

            bool ok = board.tryMove(sfFile, sfRank, tfFile, tfRank);
            if (ok) {
              // Build move message
              std::wstring msg = std::wstring(colorWord(mover->getColor())) + L" " +
                pieceWord(mover->getType()) + L" from " +
                toAlgebraic(sfFile, sfRank) + L" to " +
                toAlgebraic(tfFile, tfRank);
              if (target) {
                msg += std::wstring(L", capturing ") +
                  colorWord(target->getColor()) + L" " +
                  pieceWord(target->getType());
              }
              announcer.speak(msg);

              selected.reset();
              view.clearSelected();
            }
            else {
              announcer.speak(L"Illegal move.");
            }
          }
          else {
            announcer.speak(L"No piece selected. Press Space to select a piece first.");
          }
          break;
        }

        default: break;
        }

        if (movedCursor) {
          auto [f, r] = view.getCursor();
          const bool dark = VisualView::isDarkSquare(f, r);
          const wchar_t* col = dark ? L"Black" : L"White";

          if (const Piece* p = board.getPiece(f, r)) {
            std::wstring s = std::wstring(col) + L" " + toAlgebraic(f, r) +
              L", occupied by " + colorWord(p->getColor()) +
              std::wstring(L" ") + pieceWord(p->getType());
            announcer.speak(s);
          }
          else {
            std::wstring s = std::wstring(col) + L" " + toAlgebraic(f, r) + L", empty";
            announcer.speak(s);
          }
        }
      }
    }

    window.clear();
    view.draw(window);
    window.display();
  }

  return 0;
}