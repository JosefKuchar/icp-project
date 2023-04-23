#pragma once

#include <unordered_map>
#include <vector>
#include "../maploader.hpp"
#include "boost_libs/boost/serialization/vector.hpp"
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

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& playerPosition;
        ar& ghostPositions;
        ar& keyPositions;
        ar& state;
    };
};

class Game {
    Player m_player;
    Point m_finish;
    std::vector<Ghost> m_ghosts;
    std::unordered_map<Point, bool> keys;
    Map m_map;
    GameState m_gameState;

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
        return info;
    }
};
