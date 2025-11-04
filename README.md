# Rooks: Accessible Chess in Modern C++ and SFML 3

Rooks is an accessible chess game written in modern C++20 using SFML 3.  
It was inspired by my desire to bond with my daughter, who has Autism and a deep love of chess.  
As a blind developer and father, I created Rooks so we could enjoy the game together in a way that is both accessible and inclusive.  
Rooks can be played entirely with the keyboard for blind or visually impaired players, or with the mouse for sighted players.  
It uses the Windows Speech API (SAPI) for spoken feedback, allowing players who are blind or visually impaired but not yet familiar with screen readers like JAWS or NVDA to play immediately.  
Future updates will add the option to disable SAPI output and rely on existing screen readers instead.  
The project demonstrates clean MVC architecture, accessibility-focused design, and modern C++ development practices.

---

## Features
- 8x8 chessboard with move validation and game logic
- Keyboard-only control scheme
- Spoken announcements using Windows SAPI
- Modular MVC architecture with model, view, and controller layers
- Cross-platform build through CMake and vcpkg (voice available only on Windows)

---

## Requirements
- Windows 10 or later
- CMake 3.24 or newer
- A C++20 compatible compiler (MSVC, Clang-CL, or MinGW-w64)
- vcpkg package manager (environment variable VCPKG_ROOT set)
- No manual SFML installation required. The vcpkg manifest automatically handles dependencies.

---

## Build and Run

This project includes a CMakePresets.json file, which defines a default build configuration.  
You can configure and build the entire project with only two commands.

git clone https://github.com/<yourusername>/rooks.git
cd rooks

# Configure and build using presets
cmake --preset default
cmake --build --preset build

# Run
.\build\Rooks.exe
 
(Use backslashes on Windows PowerShell and forward slashes on Linux or macOS.)
 
Controls
Key
Action
Arrow Keys
Move cursor on the board
Space
Select or deselect a piece
Enter
Move the selected piece to the current square
Alt + F4
Exit the game
 
Project Structure
src/
 ├── model/        # Board, pieces, rules
 ├── view/         # VisualView renderer, Announcer (SAPI)
 ├── controller/   # InputController (keyboard and mouse)
 └── main.cpp      # Entry point
assets/            # Sounds, textures, and other resources
vcpkg.json         # Manifest for SFML dependency
CMakeLists.txt     # Build definition
CMakePresets.json  # Preset configurations for easy setup
 
 
Accessibility

Voice announcements use the Windows Speech API (SAPI).
On non-Windows systems, the game runs without voice output.

The interface supports screen readers and keyboard-only input.

Future versions will add sound cues and optional NVDA or JAWS integration.
 
Development Notes
vcpkg Manifest
This project uses a vcpkg manifest to define dependencies and lock their versions.

{
  "name": "rooks",
  "version-string": "1.0.0",
  "builtin-baseline": "1b4a65242adfd65a82b1d1a6f31f1accdfe09af9",
  "dependencies": [
    {
      "name": "sfml",
      "default-features": false,
      "features": ["graphics", "window", "system", "audio"]
    }
  ]
}
 
You do not need to run vcpkg install manually.
CMake reads this manifest automatically when the VCPKG_ROOT environment variable is set.
 
Known Issues

Voice output (SAPI) is only available on Windows.

The project uses SFML 3 APIs. If you are using SFML 2.5, you may need to update some code such as
sf::Mouse::Button::Left to sf::Mouse::Left.
 
Coming Soon

Graphic sprites to represent chess pieces

Ability to adjust SAPI rate, volume and enable/disable entirely

Sound cues for moves and captures

Support for en passant, castling, and pawn promotion

UI Automation hooks for NVDA and JAWS

Continuous Integration builds with GitHub Actions

Prebuilt Windows releases for easy download
 
Contributing

Fork the repository and clone your fork.

Build locally using the CMake commands above.

Create a feature branch, commit your changes, and open a pull request.
 
License
MIT License. See the LICENSE file for details.
SFML is provided under the zlib/png license.
 
## Acknowledgements
Built with SFML 3 and vcpkg, and inspired by my brilliant little girl who never stopped asking her dad to play with her, even when the answer was often, "I can't play that game because I'm blind."  
Thanks to this project, I don't have to say no anymore.
