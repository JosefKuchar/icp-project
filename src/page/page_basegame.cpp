/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_basegame.cpp
 * @brief BaseGamePage implementation
 */

#include "page_basegame.hpp"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <iostream>
#include "../mainwindow.hpp"
#include "globals.hpp"
#include "maploader.hpp"
#include "page.hpp"

BaseGamePage::BaseGamePage(QWidget* parent) : QWidget(parent) {
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
    // Add to layout
    this->layout = new QVBoxLayout(this);
    this->m_gameScene = new QGraphicsScene(this);
    this->view = new QGraphicsView(m_gameScene);
    this->layout->addWidget(view);
    this->setLayout(this->layout);
    this->setFocusPolicy(Qt::StrongFocus);
}

void BaseGamePage::resizeEvent(QResizeEvent* event) {
    this->view->fitInView(m_gameScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void BaseGamePage::drawMap(MapInfo map) {
    this->game = new Game(map);

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
        m_gameScene->addItem(object);
    }

    this->view->fitInView(m_gameScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void BaseGamePage::clear() {
    // Stop timer
    this->timer->stop();
    // Delete all objects from game scene
    this->m_gameScene->clear();
    this->m_objects.clear();
    this->m_ghosts.clear();
    this->m_keys.clear();
}

void BaseGamePage::draw(GameInfo info) {
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

void BaseGamePage::tick() {}

BaseGamePage::~BaseGamePage() {}
