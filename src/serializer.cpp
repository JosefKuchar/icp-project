/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file serializer.cpp
 * @brief Serializer implementation
 */

#include "serializer.hpp"

void Serializer::addStep(GameInfo info) {
    ticks.push_back(info);
}

Serializer::Serializer() {}

Serializer::Serializer(MapInfo map) {
    this->map = map;
}

Serializer::~Serializer() {}

GameInfo Serializer::getStep() {
    GameInfo info = ticks.front();
    ticks.erase(ticks.begin());
    return info;
}
