/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file ghost.cpp
 * @brief Ghost implementation
 */

#include "ghost.hpp"
#include <random>
#include "direction.hpp"

Ghost::Ghost(Map* map, Point position) : Object(map, position) {}

void Ghost::tick() {
    // Move in a random direction
    while (true) {
        Direction direction = static_cast<Direction>(rand() % 4);
        if (!this->map->isInWall(this->position + direction)) {
            this->position += direction;
            break;
        }
    }
}

Ghost::~Ghost() {}
