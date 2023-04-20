#pragma once

#include "point.hpp"
#include <vector>

class Map {
    std::vector<std::vector<bool>> m_map;
    int m_width, m_height;

    public:
        Map();
        Map(int, int);
        ~Map();

        bool isInWall(Point position);
};
