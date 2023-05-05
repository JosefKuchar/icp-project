/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file player.hpp
 * @brief Player header
 */

#pragma once
#include "map.hpp"
#include "object.hpp"
#include "point.hpp"
#include <vector>

enum class MovementMode {
    None,
    Keys,
    Mouse,
};

class Player : public Object {
    Point m_targetPosition;
    Direction m_direction;
    MovementMode m_movementMode;

   public:
    Player();
    Player(Map* map, Point position);
    void tick();
    std::vector<Point> calculateDirection();

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
