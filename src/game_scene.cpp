#include "game_scene.hpp"
#include <iostream>
#include "globals.hpp"

#include "empty_sprite.hpp"
#include "ghost_sprite.hpp"
#include "key_sprite.hpp"
#include "pacman_sprite.hpp"
#include "target_sprite.hpp"

GameScene::GameScene(MapInfo& map) {
    this->game = new Game(map);

    // Create all objects
    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            QPoint position(col, row);
            m_objects.append(new EmptySprite(position, this->game));
            switch (map.map[row][col]) {
                case Tile::Player:
                    m_player = new PacmanSprite(position, this->game);
                    m_objects.append(m_player);
                    break;
                case Tile::Ghost: {
                    auto ghost = new GhostSprite(position, this->game);
                    m_objects.append(ghost);
                    m_ghosts.append(ghost);
                    break;
                }
                case Tile::Wall:
                    m_objects.append(new Sprite(QPixmap(":assets/wall.png"), position, this->game));
                    break;
                case Tile::Empty:
                    break;
                case Tile::Key: {
                    auto key = new KeySprite(position, this->game);
                    m_objects.append(key);
                    m_keys.append(key);
                    break;
                }
                case Tile::Target:
                    m_objects.append(new TargetSprite(position, this->game));
                    break;
            }
        }
    }

    // Add all objects to the scene
    for (auto object : m_objects) {
        this->addItem(object);
    }
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
    for (auto& key : m_keys) {
        bool found = false;
        for (auto& keyInfo : info.keyPositions) {
            if (key->getPosition() == QPoint(keyInfo.x, keyInfo.y)) {
                found = true;
                break;
            }
        }
        key->setVisible(found);
    }
}
