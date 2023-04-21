#pragma once

#include <vector>
#include "../maploader.hpp"
#include "point.hpp"

class Map {
    std::vector<std::vector<bool>> m_map;
    int m_width, m_height;

   public:
    Map();
    Map(MapInfo map);
    ~Map();

    bool isInWall(Point position);
};
