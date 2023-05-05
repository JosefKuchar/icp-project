/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file object.cpp
 * @brief Object implementation
 */

#include "object.hpp"

Object::Object() {}

Object::Object(Map* map, Point position) {
    this->m_map = map;
    this->position = position;
}
