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

/**
 * @brief Map
 */
class Map {
   public:
    /**
     * @brief Map constructor
     */
    Map();

    /**
     * @brief Map constructor
     * @param map Map
     */
    Map(MapInfo map);
    ~Map();

    /**
     * @brief Check if position is inside wall
     * @param position Position
     */
    bool isInWall(Point position);

    /// Map data
    std::vector<std::vector<bool>> map;
    /// Width of the map
    int width;
    /// Height of the map
    int height;
};
