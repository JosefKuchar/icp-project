/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file object.hpp
 * @brief Object header
 */

#pragma once

#include "map.hpp"
#include "point.hpp"

/**
 * @brief Object
 */
class Object {
   protected:
    Map* map;

   public:
    Point position;

    /**
     * @brief Object constructor
     */
    Object();

    /**
     * @brief Object constructor
     * @param map Map
     * @param position Position
     */
    Object(Map* map, Point position);
};
