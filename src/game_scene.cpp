#include "game_scene.hpp"
#include <iostream>
#include "globals.hpp"

#include "ghost_sprite.hpp"
#include "key_sprite.hpp"
#include "pacman_sprite.hpp"
#include "target_sprite.hpp"
#include "wall_sprite.hpp"

GameScene::GameScene(MapInfo& map) {
    // Create all objects
    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            QPoint position(col, row);
            switch (map.map[row][col]) {
                case Tile::Player:
                    m_player = new PacmanSprite(position);
                    m_objects.append(m_player);
                    break;
                case Tile::Ghost: {
                    auto ghost = new GhostSprite(position);
                    m_objects.append(ghost);
                    m_ghosts.append(ghost);
                    break;
                }
                case Tile::Wall:
                    m_objects.append(new WallSprite(position));
                    break;
                case Tile::Empty:
                    break;
                case Tile::Key:
                    m_objects.append(new KeySprite(position));
                    break;
                case Tile::Target:
                    m_objects.append(new TargetSprite(position));
                    break;
            }
        }
    }

    // Add all objects to the scene
    for (auto object : m_objects) {
        this->addItem(object);
    }

    game = new Game(map);
}

GameScene::~GameScene() {
    for (auto object : m_objects) {
        delete object;
    }
}

void GameScene::start() {
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(globals::TICK_RATE);
}

void GameScene::tick() {
    this->game->tick();
    GameInfo info = this->game->getGameInfo();
    m_player->setPosition(QPoint(info.playerPosition.x, info.playerPosition.y));
    for (int i = 0; i < m_ghosts.size(); ++i) {
        m_ghosts[i]->setPosition(QPoint(info.ghostPositions[i].x, info.ghostPositions[i].y));
    }
}
