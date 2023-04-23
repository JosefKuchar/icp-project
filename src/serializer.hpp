#pragma once

#include "boost_libs/boost/archive/text_iarchive.hpp"
#include "boost_libs/boost/archive/text_oarchive.hpp"
#include <vector>
#include "game/game.hpp"
#include "maploader.hpp"

class Serializer {
private: 
     friend class boost::serialization::access;
     template<class Archive>
     void serialize(Archive &a, const unsigned version) {
          a & ticks & map;
     }

public:
     std::vector<GameInfo> ticks;
     MapInfo map;
     Serializer();
     Serializer(MapInfo);
     ~Serializer();
     void addStep(GameInfo info);
     GameInfo getStep();
};
