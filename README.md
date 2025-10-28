\# Rooks



\*\*Rooks\*\* is an accessible, cross-input chess game built in modern \*\*C++\*\* with \*\*SFML\*\* for rendering and \*\*Microsoft SAPI\*\* for speech output.  

It allows sighted and blind players to enjoy chess together through a shared interface that’s both visually interactive and fully keyboard/screen-reader navigable.



---



\## Project Goals

\- Create a simple, lightweight chess game for Windows that’s playable entirely with keyboard and sound.  

\- Present a clean MVC-based architecture demonstrating modern C++ design patterns.  

\- Showcase accessibility-first design in a C++ application using speech feedback via SAPI.



---



\## Key Features

\- \*\*Visual UI (SFML)\*\* — renders an 8×8 chessboard for sighted players.  

\- \*\*Keyboard Navigation\*\* — blind players can move a cursor with arrow keys:

&nbsp; - Space to pick up a piece  

&nbsp; - Enter to drop the piece  

&nbsp; - Ctrl + Alt + S to hear capture summary  

\- \*\*Speech Feedback (SAPI)\*\* — announces square color, piece type, and move results.  

\- \*\*Legal Move Logic\*\* — implemented using the Strategy pattern per piece type.  

\- \*\*Observer Pattern\*\* — View and Announcer react automatically to board changes.  

\- \*\*Cross-input Gameplay\*\* — sighted players use mouse; blind players use keyboard and speech.



---



\## Architecture Overview



| Layer | Responsibility | Design Pattern |

|-------|----------------|----------------|

| Model | Board, pieces, rules | Strategy (movement), Observer (notifications) |

| View | Visual board + speech announcer | Observer |

| Controller | Handles keyboard/mouse input | MVC Controller |

| App | Main loop and wiring | — |



---



\## Design Patterns Demonstrated

\- \*\*MVC (Model-View-Controller)\*\* — separates logic, rendering, and input.  

\- \*\*Strategy\*\* — each piece’s movement rules are encapsulated in a dedicated class.  

\- \*\*Observer\*\* — decouples board updates from display and speech outputs.



---



\## Build and Run



\### Prerequisites

\- Windows 10 or later  

\- CMake 3.20 or newer  

\- vcpkg for dependency management  

\- MSVC or Clang-CL compiler  

\- SFML 2.5+ installed via vcpkg  

\- Microsoft SAPI (built into Windows)



\### Clone and Build

```bash

git clone https://github.com/<yourusername>/Rooks.git

cd Rooks

cmake -B build -S . -DCMAKE\_TOOLCHAIN\_FILE=\[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake

cmake --build build --config Release



\### Run

./build/Release/Rooks.exe





\## Controls



* Arrow keys to move around the board
* Spacebar to pick up a piece or cancel carrying a piece
* Enter key to drop a piece
* ctrl + alt + s to announce a summary of captures so far in the game
* Mouse click (sighted players) select piece to move



\## Project Structure

Rooks/

├─ include/      # Headers (public interfaces)

├─ src/          # Source files (.cpp)

├─ assets/       # Sprites, fonts, etc.

├─ CMakeLists.txt

└─ vcpkg.json





\## Accessibility

Rooks uses Microsoft SAPI for spoken feedback, providing self-voicing output even outside traditional screen readers.

This ensures that blind and sighted players can play seamlessly together on the same system.



\## Contributing

Contributions are welcome. Whether you want to fix bugs, improve accessibility, or extend gameplay, your help is appreciated.



\### Fork and Build Locally



1. Fork the repository on GitHub.
2. Clone your fork
3. Install dependencies (with vcpkg): vcpkg install sfml
4. Configure and build the project: cmake -B build -S . -DCMAKE\_TOOLCHAIN\_FILE=\[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
   cmake --build build --config Release
5. Run and test: ./build/Release/Rooks.exe
6. Create a new branch for your change: git checkout -b feature/your-feature-name
7. Commit, push, and open a pull request.



\### Coding Guidelines



* Use C++17 or later
* Follow consistent naming and brace style
* Keep code accessible and modular
* Write short, descriptive commit messages



\## Coming Soon



* Add optional UI Automation support for native NVDA/JAWS integration.
* Add sound cues for moves and captures.
* Add sounds for captures and moves
* Handle advanced chess move strategies such as en passant, castling, promotion, etc.





\## License

MIT License © 2025 Tre Scinta



