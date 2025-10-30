\# Rooks - Application Roadmap



\## V1



\### Done

\-  Implemented CMake build system with vcpkg and SFML integration  

\-  Created main entry point (`main.cpp`) with event-driven game loop  

\-  Added Observer pattern (`IObserver`, `ISubject`, `Observer.h`)  

\-  Integrated SAPI voice output system (`Announcer`) for accessible audio feedback  

\-  Built minimal `VisualView` for rendering 8×8 chessboard and cursor navigation  

\-  Implemented cursor-based navigation via arrow keys  

\-  Added SAPI speech for announcing square color and coordinate (e.g., "White E4")  

\-  Added voice feedback for occupied squares with piece color and type  

\-  Implemented `Piece` class with enums for color and type  

* &nbsp;Implemented `Board` class with 8×8 grid and full standard chess setup (32 pieces)  

\-  Integrated rendering of all 32 pieces using SFML 3 text rendering  

\-  Verified cross-component integration between `Board`, `VisualView`, and `Announcer`

\-  Add input handler/controller for selecting and moving pieces  



\### Todo

\-  Implement check/checkmate/stalemate detection  

\-  Add game reset and quit options  

\-  Conduct full accessibility QA (blind navigation, keyboard-only flow)



\### In-Progress

\-  Implement movement rules for each piece type (Rook, Knight, etc.)  



--



\## V2



\### Todo

\-  Announce legal/illegal moves with SAPI feedback  

\-  Add move highlighting for selected piece and valid destination squares  

\-  Add support for external screen readers (NVDA, JAWS)  

\-  Add configurable SAPI verbosity settings (speech rate, pitch, voice, etc.)  

\-  Add option to disable SAPI output and defer to user’s screen reader  

\-  Allow user-defined color schemes and high-contrast board themes  

\-  Implement game save/load functionality  

\-  Add true turn-based play with move counters and history tracking  

\-  Add basic UI for accessibility and customization settings  



