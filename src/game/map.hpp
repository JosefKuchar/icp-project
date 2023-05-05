/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file map.hpp
 * @brief Map header
 */

#pragma once

#include <vector>
#include "../maploader.hpp"
#include "point.hpp"

class Map {
   public:
    std::vector<std::vector<bool>> m_map;
    int m_width, m_height;
    Map();
    Map(MapInfo map);
    ~Map();

    bool isInWall(Point position);
};
