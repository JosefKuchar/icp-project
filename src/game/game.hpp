/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file game.hpp
 * @brief Game header
 */

#pragma once

#include <unordered_map>
#include <vector>
#include "../maploader.hpp"
#include "boost/serialization/vector.hpp"
#include "direction.hpp"
#include "ghost.hpp"
#include "map.hpp"
#include "player.hpp"
#include "point.hpp"

enum class GameState {
    Playing,
    Won,
    Lost,
};

struct GameInfo {
    Point playerPosition;
    std::vector<Point> ghostPositions;
    std::vector<Point> keyPositions;
    GameState state;
    size_t step;
    size_t totalKeys;

    template <typename Archive>
    void serialize(Archive& ar, [[maybe_unused]] const unsigned int version) {
        ar& playerPosition;
        ar& ghostPositions;
        ar& keyPositions;
        ar& state;
        ar& step;
        ar& totalKeys;
    };
};

class Game {
    Player m_player;
    Point m_finish;
    std::vector<Ghost> m_ghosts;
    std::unordered_map<Point, bool> keys;
    Map m_map;
    GameState m_gameState;
    size_t step;

   public:
    Game(MapInfo map);
    ~Game();

    /**
     * @brief Update the game state
     */
    void tick();

    /**
     * @brief Set the direction of the player
     * @param direction Player direction
     */
    void setDirection(Direction direction);

    /**
     * @brief Set target position of the player
     * @param Position Target position
     */
    void setTargetPosition(Point position);

    /**
     * @brief Get the current game state
     */
    GameInfo getGameInfo() {
        GameInfo info;
        info.playerPosition = this->m_player.position;
        for (auto& ghost : this->m_ghosts) {
            info.ghostPositions.push_back(ghost.position);
        }
        for (auto& key : this->keys) {
            if (!key.second) {
                info.keyPositions.push_back(key.first);
            }
        }
        info.state = this->m_gameState;
        info.step = this->step;
        info.totalKeys = this->keys.size();
        return info;
    }
};
