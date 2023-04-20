#pragma once

#include "object.hpp"
#include "map.hpp"
#include "point.hpp"

class Ghost : public Object {
    public:
        Ghost();
        Ghost(Map *map, Point position);
        ~Ghost();

        void tick();
};
