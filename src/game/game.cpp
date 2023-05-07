/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file game.cpp
 * @brief Game implementation
 */

#include "game.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

Game::Game(MapInfo map) {
    this->step = 0;
    this->gameState = GameState::Playing;
    this->map = Map(map);
    // Initialize from map
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            switch (map.map[y][x]) {
                case Tile::Player:
                    this->player = Player(&this->map, Point(x, y));
                    break;
                case Tile::Ghost:
                    this->ghosts.push_back(Ghost(&this->map, Point(x, y)));
                    break;
                case Tile::Key:
                    this->keys[Point(x, y)] = false;
                    break;
                case Tile::Target:
                    this->finish = Point(x, y);
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::tick() {
    // Don't tick if game is not running
    if (this->gameState != GameState::Playing) {
        return;
    }

    // Save previous positions
    Point prev_pos = this->player.position;
    std::vector<Point> prev_ghosts_pos;
    std::transform(this->ghosts.begin(), this->ghosts.end(), std::back_inserter(prev_ghosts_pos),
                   [](auto& ghost) { return ghost.position; });

    // Update player
    this->player.tick();

    // Update ghosts
    for (auto& ghost : this->ghosts) {
        ghost.tick();
    }

    // Update tick counter
    this->step++;

    // Check for collision with ghost
    for (size_t i = 0; i < ghosts.size(); i++) {
        if (this->player.position == this->ghosts[i].position ||
            (prev_pos == this->ghosts[i].position && this->player.position == prev_ghosts_pos[i])) {
            std::cout << "Lost!" << std::endl;
            this->gameState = GameState::Lost;
            return;
        }
    }
    // Check for collisions with keys
    if (this->keys.count(this->player.position)) {
        this->keys[this->player.position] = true;
    }

    // Check if all keys are collected
    if (std::all_of(this->keys.begin(), this->keys.end(), [](auto& key) { return key.second; }) &&
        this->player.position == this->finish) {
        std::cout << "Won!" << std::endl;
        this->gameState = GameState::Won;
    }
}

void Game::setDirection(Direction direction) {
    this->player.setDirection(direction);
}

void Game::setTargetPosition(Point position) {
    this->player.setTargetPosition(position);
}

GameInfo Game::getGameInfo() {
    GameInfo info;
    info.playerPosition = this->player.position;
    for (auto& ghost : this->ghosts) {
        info.ghostPositions.push_back(ghost.position);
    }
    for (auto& key : this->keys) {
        if (!key.second) {
            info.keyPositions.push_back(key.first);
        }
    }
    info.state = this->gameState;
    info.step = this->step;
    info.totalKeys = this->keys.size();
    return info;
}
