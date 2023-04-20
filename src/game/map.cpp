#include "map.hpp"

Map::Map() {};

Map::Map(int width, int height) {
    this->m_width = width;
    this->m_height = height;
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
