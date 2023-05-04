#include "game_scene.hpp"
#include <fstream>
#include <iostream>
#include "globals.hpp"

GameScene::GameScene(MapInfo& map) {
    this->game = new Game(map);
    this->serializer = Serializer(map);
    // {
    //     std::ifstream infile("haha.icpacman");
    //     boost::archive::text_iarchive archive2(infile);
    //     archive2 >> this->serializer;
    // }

    // Create all objects
    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            QPoint position(col, row);
            m_objects.append(new Sprite(QPixmap(":assets/grass.png"), position, -1, this->game));
            switch (map.map[row][col]) {
                case Tile::Player:
                    m_player = new Sprite(QPixmap(":assets/pacman.png"), position, 10, this->game);
                    m_objects.append(m_player);
                    break;
                case Tile::Ghost: {
                    auto ghost = new Sprite(QPixmap(":assets/ghost.png"), position, 20, this->game);
                    m_objects.append(ghost);
                    m_ghosts.append(ghost);
                    break;
                }
                case Tile::Wall:
                    m_objects.append(
                        new Sprite(QPixmap(":assets/wall.png"), position, 0, this->game));
                    break;
                case Tile::Empty:
                    break;
                case Tile::Key: {
                    auto key = new Sprite(QPixmap(":assets/key.png"), position, 0, this->game);
                    m_objects.append(key);
                    m_keys.append(key);
                    break;
                }
                case Tile::Target:
                    m_objects.append(
                        new Sprite(QPixmap(":assets/target.png"), position, 0, this->game));
                    break;
            }
        }
    }
    // Draw walls around the map
    for (int row = -1; row <= map.height; row++) {
        m_objects.append(new Sprite(QPixmap(":assets/wall.png"), QPoint(-1, row), 0, this->game));
        m_objects.append(
            new Sprite(QPixmap(":assets/wall.png"), QPoint(map.width, row), 0, this->game));
    }
    for (int col = 0; col < map.width; col++) {
        m_objects.append(new Sprite(QPixmap(":assets/wall.png"), QPoint(col, -1), 0, this->game));
        m_objects.append(
            new Sprite(QPixmap(":assets/wall.png"), QPoint(col, map.height), 0, this->game));
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
    if (info.state != GameState::Playing) {
    }

    // this->serializer.addStep(info);

    // GameInfo info = this->serializer.getStep();
    // if (info.state != GameState::Playing) {
    //     exit(0);
    // }

    // if (info.state != GameState::Playing) {
    //     // Serialize shit
    //     {
    //         std::ofstream outfile("haha.icpacman");
    //         boost::archive::text_oarchive archive(outfile);
    //         archive << this->serializer;
    //         std::cout << "HEHE" << std::endl;
    //     }
    //}

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
