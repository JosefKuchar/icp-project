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

/**
 * @brief Game state
 */
enum class GameState {
    Playing,
    Won,
    Lost,
};

/**
 * @brief Game info inteface for drawing
 */
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

/**
 * @brief Game logic
 */
class Game {
    /// Player
    Player player;
    /// Finish coordinates
    Point finish;
    /// Ghost list
    std::vector<Ghost> ghosts;
    /// Key list (position, collected)
    std::unordered_map<Point, bool> keys;
    /// Map
    Map map;
    /// State
    GameState gameState;
    /// Step counter
    size_t step;

   public:
    /**
     * @brief Game constructor
     * @param map Map
     */
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
     * @brief Get the current game state for drawing
     */
    GameInfo getGameInfo();
};
