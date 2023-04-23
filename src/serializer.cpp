#include "serializer.hpp"

void Serializer::addStep(GameInfo info) {
    ticks.push_back(info);
}

Serializer::Serializer(){}

Serializer::Serializer(MapInfo map){
    this->map = map;
}

Serializer::~Serializer(){}

GameInfo Serializer::getStep() {
    GameInfo info = ticks.front();
    ticks.erase(ticks.begin());
    return info;
}
