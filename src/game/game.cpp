#include "game.hpp"

#include <algorithm>

Game::Game(MapInfo map) {
    this->m_gameState = GameState::Playing;
    this->m_map = Map(map);
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            switch (map.map[y][x]) {
                case Tile::Player:
                    this->m_player = Player(&this->m_map, Point(x, y));
                    break;
                case Tile::Ghost:
                    this->m_ghosts.push_back(Ghost(&this->m_map, Point(x, y)));
                    break;
                case Tile::Key:
                    this->keys[Point(x, y)] = false;
                    break;
                case Tile::Target:
                    this->m_finish = Point(x, y);
                    break;
            }
        }
    }
}

void Game::tick() {
    if (this->m_gameState != GameState::Playing) {
        return;
    }
    // Update player
    this->m_player.tick();
    // Update ghosts
    for (auto& ghost : this->m_ghosts) {
        ghost.tick();
    }
    // Check for collisions with ghosts
    for (auto& ghost : this->m_ghosts) {
        if (this->m_player.position == ghost.position) {
            this->m_gameState = GameState::Lost;
            return;
        }
    }

    // Check for collisions with keys
    if (this->keys.count(this->m_player.position)) {
        this->keys[this->m_player.position] = true;
    }

    // Check if all keys are collected
    if (std::all_of(this->keys.begin(), this->keys.end(), [](auto& key) { return key.second; }) &&
        this->m_player.position == this->m_finish) {
        this->m_gameState = GameState::Won;
    }
}

void Game::setDirection(Direction direction) {
    this->m_player.setDirection(direction);
}

void Game::setTargetPosition(Point position) {
    this->m_player.setTargetPosition(position);
}
