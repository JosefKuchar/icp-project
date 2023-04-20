#include "game.hpp"

#include <algorithm>

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
    if (std::all_of(this->keys.begin(), this->keys.end(), [](auto& key) {
        return key.second;
    }) && this->m_player.position == this->m_finish) {
        this->m_gameState = GameState::Won;
    }

}

void Game::setDirection(Direction direction) {
    this->m_player.setDirection(direction);
}

void Game::setTargetPosition(Point position) {
    this->m_player.setTargetPosition(position);
}
