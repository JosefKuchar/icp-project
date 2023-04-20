#include "object.hpp"

Object::Object(Map *map, Point position) {
    this->m_map = map;
    this->position = position;
}
