/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file serializer.cpp
 * @brief Serializer implementation
 */

#include "serializer.hpp"

Serializer::Serializer() {}

Serializer::~Serializer() {}

void Serializer::addStep(GameInfo info) {
    ticks.push_back(info);
}

void Serializer::clearSteps() {
    ticks.clear();
}

GameInfo Serializer::getStep(size_t index) {
    return this->ticks[index];
}

MapInfo Serializer::getMap() {
    return this->map;
}

void Serializer::setMap(MapInfo map) {
    this->map = map;
}

size_t Serializer::getStepsCount() {
    return this->ticks.size();
}
