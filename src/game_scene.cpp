#include "game_scene.hpp"
#include <iostream>
#include "globals.hpp"

#include "ghost_sprite.hpp"
#include "key_sprite.hpp"
#include "pacman_sprite.hpp"
#include "target_sprite.hpp"
#include "wall_sprite.hpp"

Grid::Grid(MapInfo& map) {
    // Create all objects
    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            QPoint position(col, row);
            switch (map.map[row][col]) {
                case Tile::Player:
                    m_player = new PacmanSprite(position);
                    m_objects.append(m_player);
                    break;
                case Tile::Ghost:
                    m_objects.append(new GhostSprite(position));
                    break;
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
}

Grid::~Grid() {
    for (auto object : m_objects) {
        delete object;
    }
}

void Grid::setDirection(QPoint direction) {
    m_direction = direction;
}

void Grid::start() {
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start(globals::TICK_RATE);
}

void Grid::tick() {
    auto playerPos = m_player->getPosition();
    m_player->setPosition(playerPos + m_direction);
}
