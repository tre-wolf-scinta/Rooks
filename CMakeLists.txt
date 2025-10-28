cmake_minimum_required(VERSION 3.20)
project(Rooks CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If you want this baked in, keep the toolchain line.
# Otherwise you can pass it on the CLI at configure time.
set(CMAKE_TOOLCHAIN_FILE
    "C:/Users/tre_s/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file" FORCE)

# --- SFML 3 style find + targets ---
# vcpkg output told us to use CONFIG mode and these component names.
find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

add_executable(Rooks
    src/app/main.cpp
    src/model/Board.cpp
    src/model/Piece.cpp
    src/strategy/KnightStrategy.cpp
    src/strategy/BishopStrategy.cpp
    src/strategy/RookStrategy.cpp
    src/strategy/QueenStrategy.cpp
    src/strategy/KingStrategy.cpp
    src/strategy/PawnStrategy.cpp
    src/view/VisualView.cpp
    src/view/Announcer.cpp
    src/controller/InputController.cpp
)

target_include_directories(Rooks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link SFML 3 targets (note the casing and namespace)
target_link_libraries(Rooks PRIVATE SFML::Graphics SFML::Window SFML::System)

# SAPI speech uses COM on Windows
if(WIN32)
    target_link_libraries(Rooks PRIVATE ole32)
endif()

# Put the exe in build/bin/
set_target_properties(Rooks PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
