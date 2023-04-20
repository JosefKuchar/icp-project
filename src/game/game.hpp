#pragma once

#include "direction.hpp"
#include "point.hpp"
#include <vector>
#include <unordered_map>
#include "player.hpp"
#include "ghost.hpp"

enum class GameState {
    Playing,
    Won,
    Lost,
};

class Game {
    
    Player m_player;
    Point m_finish;
    std::vector<Ghost> m_ghosts;
    std::unordered_map<Point, bool> keys;
    std::vector<std::vector<bool>> m_map;
    GameState m_gameState;

   public:
    Game();
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
};
