/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file map.cpp
 * @brief Map implementation
 */

#include "map.hpp"

Map::Map(){};

Map::Map(MapInfo map) {
    this->m_width = map.width;
    this->m_height = map.height;
    this->m_map = std::vector<std::vector<bool>>(map.height, std::vector<bool>(map.width, false));
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            if (map.map[y][x] == Tile::Wall) {
                this->m_map[y][x] = true;
            }
        }
    }
};

bool Map::isInWall(Point position) {
    // Everything outside the map is a wall
    if (position.x < 0 || position.x >= m_width) {
        return true;
    } else if (position.y < 0 || position.y >= m_height) {
        return true;
    } else {
        return this->m_map[position.y][position.x];
    }
};

Map::~Map(){};
