/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file ghost.hpp
 * @brief Ghost header
 */

#pragma once

#include "map.hpp"
#include "object.hpp"
#include "point.hpp"

/**
 * @brief Ghost
 */
class Ghost : public Object {
   public:
    /**
     * @brief Ghost constructor
     */
    Ghost();

    /**
     * @brief Ghost constructor
     * @param map Map
     * @param position Position
     */
    Ghost(Map* map, Point position);
    ~Ghost();

    /**
     * @brief Update ghost position
     */
    void tick();
};
