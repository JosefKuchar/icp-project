/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file game.cpp
 * @brief Game implementation
 */

#include "game.hpp"

#include <algorithm>
#include <iostream>

#include <fstream>

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

Game::Game(MapInfo map) {
    this->step = 0;
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
                default:
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

    Point prev_pos = this->m_player.position;

    std::vector<Point> prev_ghosts_pos;
    std::transform(this->m_ghosts.begin(), this->m_ghosts.end(),
                   std::back_inserter(prev_ghosts_pos), [](auto& ghost) { return ghost.position; });

    this->m_player.tick();
    // Update ghosts
    for (auto& ghost : this->m_ghosts) {
        ghost.tick();
    }

    this->step++;
    // Check for collision with ghost
    for (int i = 0; i < m_ghosts.size(); i++) {
        if (this->m_player.position == m_ghosts[i].position or
            (prev_pos == m_ghosts[i].position and this->m_player.position == prev_ghosts_pos[i])) {
            std::cout << "Lost!" << std::endl;
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
        std::cout << "Won!" << std::endl;
        this->m_gameState = GameState::Won;
    }
}

void Game::setDirection(Direction direction) {
    this->m_player.setDirection(direction);
}

void Game::setTargetPosition(Point position) {
    this->m_player.setTargetPosition(position);
}
