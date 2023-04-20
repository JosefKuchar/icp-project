#pragma once

#include "point.hpp"
#include "map.hpp"

class Object {
    protected:
      Map* m_map;

    public:
      Point position;
      Object(Map *map, Point position);
};
