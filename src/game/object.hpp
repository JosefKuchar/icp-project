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
