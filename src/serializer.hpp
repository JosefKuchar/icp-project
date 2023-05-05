/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file serializer.hpp
 * @brief Serializer header
 */

#pragma once

#include <vector>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "game/game.hpp"
#include "maploader.hpp"

class Serializer {
   private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& a, const unsigned version) {
        a& ticks& map;
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
