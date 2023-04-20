#include "player.hpp"

Player::Player(Map *map, Point position) : Object(map, position) {
    this->m_movementMode = MovementMode::None;
    this->m_direction = Direction::Up;
    this->m_targetPosition = Point(0, 0);
}

void Player::tick() {
    if (this->m_movementMode == MovementMode::None) {
        return;
    } else if (this->m_movementMode == MovementMode::Keys) {
        if (!this->m_map->isInWall(this->position + this->m_direction)) {
            this->position += this->m_direction;
        }
    } else {
        // TODO
        return;
    }
}

void Player::setDirection(Direction direction) {
  this->m_direction = direction;
  this->m_movementMode = MovementMode::Keys;
}

void Player::setTargetPosition(Point position) {
  this->m_targetPosition = position;
  this->m_movementMode = MovementMode::Mouse;
}
