# Project Settings

## Goal

Create a 2D offline tower defense game inspired by Wintermaul TD, designed as both a playable game and a learning project in C++, game development, GUI design, architecture, and testing.

## Technology

- Language: C++
- Standard: C++20
- Framework: Raylib
- Local Windows workflow: VS Code C++ extension with the Raylib `w64devkit` Makefile path
- Portable build system: CMake
- Testing: GoogleTest for core logic
- Initial target: Desktop
- Future consideration: Mobile app portability
- Version control: Git

## Rendering and View

- Use a 2D top-down view.
- Represent the playfield as a hex grid.
- Add debug overlay support early.
- Keep rendering separate from game logic.

## Grid Model

- Store grid positions using row/column offset coordinates.
- Derive each hex center from row, column, and row parity.
- Each tile represents one full hexagon.
- Towers occupy one full hex.
- Towers are impassable to normal movement.

## Map and Navigation

- Enemies move from spawn to exit through an ordered list of waypoints.
- Waypoints are tile-based.
- Spawn, waypoint, and exit tiles are not buildable.
- Normal enemy movement uses passable tiles only.

## Blocking and Breach Mode

- Players may place towers such that no normal path remains to the next waypoint.
- If no valid path exists, enemies enter breach mode.
- In breach mode, enemies move by the most direct route toward the next waypoint and ignore tower collision.

## Game Architecture

- Separate game logic from rendering and input.
- Use fixed timestep updates for game logic.
- Keep core systems testable without graphics.
- Prefer small systems with clear responsibilities while learning.

## Development Workflow

- Prefer VS Code for day-to-day editing, running, and debugging on Windows.
- Use `.vscode/tasks.json` and `.vscode/launch.json` for the local Run and Debug flow.
- Keep CMake available as the portable build and GoogleTest test path.
- Do not let VS Code-specific setup leak into graphics-free core logic.

## C++ Coding Style

- Use lower camel naming for local variables and free functions, for example `fixedDeltaSeconds`.
- Methods start with a lower-case letter, for example `isBuildable()` and `placeTower()`.
- Data members start with an upper-case letter, for example `Rows`, `Cols`, and `Tiles`.
- Type definitions such as structs and classes start with a lower-case `t`, for example `tHexGrid`.
- Put the opening curly brace for a new code section on its own line.

## Initial Systems

- Grid system
- Tile occupancy and build validation
- Waypoint system
- Enemy movement
- Pathfinding
- Tower placement
- Debug and logging tools

## Debug Features

- Toggle tile coordinates.
- Toggle occupancy and buildability overlay.
- Toggle path visualization.
- Toggle waypoint markers.
- Show an event log for actions such as placement, movement, and attacks.

## Early Non-Goals

- Save/load system
- Multiplayer
- Advanced visual effects
- Data-driven balancing files in the first milestone

## Planned Future Extensions

- Configurable tower and enemy classes loaded from files.
- Elemental strengths and weaknesses.
- Mobile deployment.
- Possible multiplayer mode.

## Elemental Direction

The current design direction is to start with tower upgrade classes such as fire, ice, and lightning. Later enemy waves may also have classes. Fire should lean toward stronger attacks, ice toward defense and slowing effects, and lightning toward faster attacks or movement-related effects.
