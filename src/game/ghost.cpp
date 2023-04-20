#include "ghost.hpp"
#include "direction.hpp"
#include <random>

Ghost::Ghost(Map *map, Point position) : Object(map, position) {}

void Ghost::tick() {
    // Move in a random direction
    Direction direction = static_cast<Direction>(rand() % 4);
    if (!this->m_map->isInWall(this->position + direction)) {
        this->position += direction;
    }
}