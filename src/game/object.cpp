#include "object.hpp"

Object::Object() {}

Object::Object(Map* map, Point position) {
    this->m_map = map;
    this->position = position;
}
