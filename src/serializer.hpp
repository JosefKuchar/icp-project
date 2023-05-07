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

/**
 * @brief Game step info used for serialization
 */
class Serializer {
   public:
    /**
     * @brief Serializer constructor (without map or steps)
     */
    Serializer();
    ~Serializer();

    /**
     * @brief Add game step
     * @param info Game step info
     */
    void addStep(GameInfo info);

    /**
     * @brief Clear all steps
     */
    void clearSteps();

    /**
     * @brief Get game step
     * @param index Step index
     */
    GameInfo getStep(size_t index);

    /**
     * @brief Get map
     */
    MapInfo getMap();

    /**
     * @brief Set map
     */
    void setMap(MapInfo map);

    /**
     * @brief Get steps count
     */
    size_t getStepsCount();

   private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& a, [[maybe_unused]] const unsigned version) {
        a& ticks& map;
    }

    std::vector<GameInfo> ticks;
    MapInfo map;
};
