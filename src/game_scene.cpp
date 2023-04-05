#include "game_scene.hpp"
#include <iostream>
#include "globals.hpp"
#include "object.hpp"

Grid::Grid(MapInfo& map) {
    QPixmap pacmanPixmap(":assets/pacman.png");
    QPixmap ghostPixmap(":assets/ghost.png");
    QPixmap wallPixmap(":assets/wall.png");
    QPixmap emptyPixmap(":assets/empty.png");
    QPixmap keyPixmap(":assets/key.png");
    QPixmap targetPixmap(":assets/target.png");

    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            switch (map.map[row][col]) {
                case Tile::Player:
                    m_spritePixmap = pacmanPixmap;
                    break;
                case Tile::Ghost:
                    m_spritePixmap = ghostPixmap;
                    break;
                case Tile::Wall:
                    m_spritePixmap = wallPixmap;
                    break;
                case Tile::Empty:
                    m_spritePixmap = emptyPixmap;
                    break;
                case Tile::Key:
                    m_spritePixmap = keyPixmap;
                    break;
                case Tile::Target:
                    m_spritePixmap = targetPixmap;
                    break;
            }
            Sprite* sprite = new Sprite(m_spritePixmap);
            sprite->setPos(col * (m_spritePixmap.width()), row * (m_spritePixmap.height()));
            addItem(sprite);
            m_sprites.append(sprite);
        }
    }

    m_player = new Object(pacmanPixmap);
    addItem(m_player);
    std::cout << "Initialized grid" << std::endl;
}

void Grid::setDirection(QPoint direction) {
    std::cout << "Direction: " << direction.x() << ", " << direction.y() << std::endl;
    std::cout << "Setting direction" << std::endl;
    std::cout << m_sprites.size() << std::endl;
    m_direction = direction;
}

void Grid::start() {
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(testSlot()));
    timer->start(globals::TICK_RATE);
}

void Grid::testSlot() {
    auto playerPos = m_player->getPosition();
    auto newPos = playerPos + m_direction;
    m_player->setPosition(newPos.x(), newPos.y());
}
