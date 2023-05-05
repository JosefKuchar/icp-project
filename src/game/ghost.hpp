/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file ghost.hpp
 * @brief Ghost header
 */

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
