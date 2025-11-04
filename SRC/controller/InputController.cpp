// Implements InputController.h to handle user keyboard and mouse inputs.

#include "controller/InputController.h"
#include <SFML/Graphics.hpp>            
#include "model/Board.h"                
#include "view/VisualView.h"            
#include "view/Announcer.h"             
#include <string>                       

// Internal Helpers -- Not exposed in header
namespace {
  static std::wstring toAlgebraic(int file, int rank) {
    wchar_t f = static_cast<wchar_t>(L'A' + file);
    wchar_t r = static_cast<wchar_t>(L'1' + rank);
    std::wstring out; out.push_back(f); out.push_back(r);
    return out;
  }

  static const wchar_t* colorWord(PieceColor color) {
    return (color == PieceColor::White) ? L"White" : L"Black";
  }

  static const wchar_t* pieceWord(PieceType type) {
    switch (type) {
    case PieceType::King:   return L"King";
    case PieceType::Queen:  return L"Queen";
    case PieceType::Rook:   return L"Rook";
    case PieceType::Bishop: return L"Bishop";
    case PieceType::Knight: return L"Knight";
    case PieceType::Pawn:   return L"Pawn";
    }
    return L"Piece";
  }
} 

//  Ctor 
InputController::InputController(Board& board,
  VisualView& view,
  Announcer& announcer,
  sf::RenderWindow& window,
  unsigned tileSize)
  : board_(board),
  view_(view),
  announcer_(announcer),
  window_(window),
  tileSize_(tileSize) {}

//  Public access point 
void InputController::handleEvent(const sf::Event& ev, bool& running) {
  if (ev.is<sf::Event::Closed>()) {
    running = false;
    window_.close();
    return;
  }

  if (const auto* mb = ev.getIf<sf::Event::MouseButtonPressed>()) {
    if (mb->button == sf::Mouse::Button::Left) {
      handleMouseButtonPressed(*mb);
    }
  }

  if (const auto* key = ev.getIf<sf::Event::KeyPressed>()) {
    handleKeyPressed(*key, running);
  }
}

//  Mouse 
void InputController::handleMouseButtonPressed(const sf::Event::MouseButtonPressed&) {
  auto boardCoords = mouseToBoard();
  if (!boardCoords) return;

  auto [f, r] = *boardCoords;

  if (!selected_) {
    // Try to select a piece
    if (const Piece* p = board_.getPiece(f, r)) {
      selected_ = std::make_pair(f, r);
      view_.setSelected(selected_);

      std::wstring msg = std::wstring(L"Selected ") +
        colorWord(p->getColor()) + L" " +
        pieceWord(p->getType()) + L" at " +
        toAlgebraic(f, r);
      announcer_.speak(msg);
    }
    else {
      announcer_.speak(L"No piece on this square to select.");
    }
  }
  else {
    // Try to move selected piece or deselect if same square
    auto [sfFile, sfRank] = *selected_;
    if (sfFile == f && sfRank == r) {
      clearSelection();
      announcer_.speak(L"Selection cleared.");
    }
    else {
      tryMoveSelectedTo(f, r);
    }
  }
}

//  Keyboard 
void InputController::handleKeyPressed(const sf::Event::KeyPressed& key, bool& running) {
  bool movedCursor = false;

  switch (key.scancode) {
  case sf::Keyboard::Scancode::Left:  view_.moveCursor(-1, 0); movedCursor = true; break;
  case sf::Keyboard::Scancode::Right: view_.moveCursor(+1, 0); movedCursor = true; break;
  case sf::Keyboard::Scancode::Up:    view_.moveCursor(0, +1); movedCursor = true; break;
  case sf::Keyboard::Scancode::Down:  view_.moveCursor(0, -1); movedCursor = true; break;

  case sf::Keyboard::Scancode::Escape:
    running = false; window_.close(); return;

  case sf::Keyboard::Scancode::Space: {
    auto [f, r] = view_.getCursor();
    if (!selected_) {
      if (const Piece* p = board_.getPiece(f, r)) {
        selected_ = std::make_pair(f, r);
        view_.setSelected(selected_);
        std::wstring msg = std::wstring(L"Selected ") +
          colorWord(p->getColor()) + L" " +
          pieceWord(p->getType()) + L" at " +
          toAlgebraic(f, r);
        announcer_.speak(msg);
      }
      else {
        announcer_.speak(L"No piece on this square to select.");
      }
    }
    else {
      clearSelection();
      announcer_.speak(L"Selection cleared.");
    }
    break;
  }

  case sf::Keyboard::Scancode::Enter: {
    if (selected_) {
      auto [sfFile, sfRank] = *selected_;
      auto [tfFile, tfRank] = view_.getCursor();

      if (sfFile == tfFile && sfRank == tfRank) {
        announcer_.speak(L"Cannot drop on the same square.");
        break;
      }
      tryMoveSelectedTo(tfFile, tfRank);
    }
    else {
      announcer_.speak(L"No piece selected. Press Space to select a piece first.");
    }
    break;
  }

  default: break;
  }

  if (movedCursor) {
    announceCursorSquare();
  }
}

//  Helpers 
std::optional<std::pair<int, int>> InputController::mouseToBoard() {
  auto mousePos = sf::Mouse::getPosition(window_);
  if (mousePos.x < 0 || mousePos.y < 0) return std::nullopt;

  int file = mousePos.x / static_cast<int>(tileSize_);
  int rank = 7 - (mousePos.y / static_cast<int>(tileSize_));

  if (file < 0 || file > 7 || rank < 0 || rank > 7) return std::nullopt;
  return std::make_pair(file, rank);
}

void InputController::announceCursorSquare() {
  auto [f, r] = view_.getCursor();
  const bool dark = VisualView::isDarkSquare(f, r);
  const wchar_t* col = dark ? L"Black" : L"White";

  if (const Piece* p = board_.getPiece(f, r)) {
    std::wstring s = std::wstring(col) + L" " + toAlgebraic(f, r) +
      L", occupied by " + colorWord(p->getColor()) +
      std::wstring(L" ") + pieceWord(p->getType());
    announcer_.speak(s);
  }
  else {
    std::wstring s = std::wstring(col) + L" " + toAlgebraic(f, r) + L", empty";
    announcer_.speak(s);
  }
}

void InputController::tryMoveSelectedTo(int f, int r) {
  if (!selected_) return;

  auto [sfFile, sfRank] = *selected_;
  const Piece* mover = board_.getPiece(sfFile, sfRank);
  const Piece* target = board_.getPiece(f, r);

  bool ok = board_.tryMove(sfFile, sfRank, f, r);
  if (ok) {
    std::wstring msg = std::wstring(colorWord(mover->getColor())) + L" " +
      pieceWord(mover->getType()) + L" from " +
      toAlgebraic(sfFile, sfRank) + L" to " +
      toAlgebraic(f, r);
    if (target) {
      msg += std::wstring(L", capturing ") +
        colorWord(target->getColor()) + L" " +
        pieceWord(target->getType());
    }
    announcer_.speak(msg);
    clearSelection();
  }
  else {
    announcer_.speak(L"Illegal move.");
  }
}

void InputController::clearSelection() {
  selected_.reset();
  view_.clearSelected();
}