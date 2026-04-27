# Game Maul TD

Game Maul TD is a 2D offline tower defense game inspired by the Wintermaul TD maps from Warcraft 3: The Frozen Throne. The project is also a learning space for C++, game development, GUI design, architecture, testing, and iterative local development.

## Project Goal

Build a playable desktop tower defense game where enemies enter from the top of a hexagonal playfield, follow tile-based waypoints, and exit at the bottom. The player places towers on full hex tiles to create maze-like paths that keep enemies under fire for as long as possible. The game is lost after enough enemies exit.

The early focus is on simple, testable systems:

- Hex grid representation
- Tile occupancy and build validation
- Waypoints and pathfinding
- Enemy movement
- Tower placement
- Debug overlays and event logging

## Technology

- Language: C++
- Framework: Raylib
- Build system: CMake
- Testing: GoogleTest for graphics-free core logic
- Initial target: Desktop
- Future consideration: Mobile portability

The project should keep game logic separate from rendering and input so the important rules can be tested without opening a window.

## Quick Start

Requirements:

- CMake 3.24 or newer
- A C++20 compiler
- Git

Configure, build, and test:

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Run the app after building:

```powershell
.\build\Debug\maultd.exe
```

The first CMake configure downloads Raylib and GoogleTest through CMake `FetchContent`.

## Core Game Rules

- The map is a hexagonal playfield stored with row/column offset coordinates.
- Hex centers are derived from row, column, and row parity.
- Each tile represents one full hexagon.
- Towers occupy one full hex and are impassable.
- Enemies move through an ordered list of tile-based waypoints.
- Spawn, waypoint, and exit tiles are not buildable.
- Normal enemy movement uses passable tiles.
- Players may block all normal paths.
- If no valid path exists to the next waypoint, enemies enter breach mode and move directly toward the next waypoint while ignoring tower collision.

## Learning Workflow

This project should be developed in small, understandable increments. Future guidance should explain tradeoffs, show the reasoning behind architecture choices, and ask clarifying questions when intent is unclear. The goal is not just to generate code, but to build the project in a way that teaches reusable game development skills.

## Early Non-Goals

- Save/load system
- Multiplayer
- Advanced visual effects
- Data-driven balancing files in the first milestone

## Project Context Files

- `AGENTS.md` contains assistant behavior and collaboration rules for future prompts.
- `docs/PROJECT_SETTINGS.md` contains the canonical design and architecture settings.
- `docs/ROADMAP.md` contains the early milestone plan.
