/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file object.hpp
 * @brief Object header
 */

#pragma once

#include "map.hpp"
#include "point.hpp"

class Object {
   protected:
    Map* m_map;

   public:
    Point position;
    Object();
    Object(Map* map, Point position);
};
