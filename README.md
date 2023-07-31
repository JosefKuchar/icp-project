# ICPacman - Pacman written in C++ (with QT)

## Hodnocení
80 / 100

## Původní README

## Team

- `xkucha28` - Josef Kuchař
- `xsirov00` - Matej Sirovatka

## Make targets
- `make` - Build project
- `make run` - Run game
- `make doxygen` - Build documentation

## Project structure
- `doc` - Documentation
- `examples` - Examples
  - `maps` - Example maps
  - `replays` - Example replays
- `src` - Source
  - `assets` - Assets (images)
  - `boost` - Boost library headers
  - `game` - Game logic (backend)
  - `page` - Pages

## Usage

### Playing
1. Run `icpacman` binary from project root
2. Click on "Start Game"
3. Select any map from `examples/maps`
4. Play using WSAD or mouse
5. After win/lose you can save replay with "Save Replay" button

### Replay
1. Run `icpacman` binary from project root
2. Click on "Load Replay"
3. Select any replay from `examples/replays`
4. Use buttons to replay selected game

## Implemented functionality

- All general requirements
- Loading arbitrary maps
- Saving and loading replays
- Collected keys and step count (interactive elements)
- WSAD and mouse movement
- All replay modes

## Architecture

Game logic (`src/game`) is separated from Qt GUI.

## References
- A* search algorithm - https://en.wikipedia.org/wiki/A*_search_algorithm
- Boost serialization library - https://www.boost.org/
