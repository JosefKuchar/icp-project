#pragma once

#include "direction.hpp"
#include "point.hpp"

class Game {
    Point m_targetPosition;

   public:
    Game();
    ~Game();

    /**
     * @brief Update the game state
     */
    void tick();

    /**
     * @brief Set the direction of the player
     * @param direction Player direction
     */
    void setDirection(Direction direction);

    /**
     * @brief Set target position of the player
     * @param x X position
     * @param y Y position
     */
    void setTargetPosition(Point position);
};
