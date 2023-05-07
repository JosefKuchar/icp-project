/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file player.hpp
 * @brief Player header
 */

#pragma once
#include <vector>
#include "map.hpp"
#include "object.hpp"
#include "point.hpp"

/**
 * @brief Movement mode
 */
enum class MovementMode {
    None,
    Keys,
    Mouse,
};

/**
 * @brief Player
 */
class Player : public Object {
   private:
    std::vector<Point> calculateDirection();
    /// Target position
    Point targetPosition;
    /// Direction
    Direction direction;
    /// Movement mode
    MovementMode movementMode;

   public:
    /**
     * @brief Player constructor
     */
    Player();

    /**
     * @brief Player constructor
     * @param map Map
     * @param position Position
     */
    Player(Map* map, Point position);

    /**
     * @brief Update player position
     */
    void tick();

    /**
     * @brief Set the direction of the player
     * @param direction Player direction
     */
    void setDirection(Direction direction);

    /**
     * @brief Set target position of the player
     * @param Position Target position
     */
    void setTargetPosition(Point position);
};
