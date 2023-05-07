/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file map.cpp
 * @brief Map implementation
 */

#include "map.hpp"

Map::Map(){};

Map::Map(MapInfo map) {
    this->width = map.width;
    this->height = map.height;
    this->map = std::vector<std::vector<bool>>(map.height, std::vector<bool>(map.width, false));
    // Set walls as true
    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            if (map.map[y][x] == Tile::Wall) {
                this->map[y][x] = true;
            }
        }
    }
};

bool Map::isInWall(Point position) {
    // Everything outside the map is a wall
    if (position.x < 0 || position.x >= width) {
        return true;
    } else if (position.y < 0 || position.y >= height) {
        return true;
    } else {
        return this->map[position.y][position.x];
    }
};

Map::~Map(){};
