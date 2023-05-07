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
    // Create timer
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
    // Initialzie widgets
    this->layout = new QVBoxLayout(this);
    this->gameScene = new QGraphicsScene(this);
    this->keyText = new QLabel(this);
    this->stepText = new QLabel(this);
    this->view = new QGraphicsView(this->gameScene);
    // Create stats layout
    QHBoxLayout* statsLayout = new QHBoxLayout();
    statsLayout->addWidget(keyText);
    statsLayout->addWidget(stepText);
    // Add to main layout
    this->layout->addLayout(statsLayout);
    this->layout->addWidget(view);
    // Set layout
    this->setLayout(this->layout);
    this->setFocusPolicy(Qt::StrongFocus);
}

void BaseGamePage::resizeEvent([[maybe_unused]] QResizeEvent* event) {
    this->view->fitInView(this->gameScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void BaseGamePage::drawMap(MapInfo map) {
    this->game = new Game(map);

    // Create all objects
    for (int row = 0; row < map.height; ++row) {
        for (int col = 0; col < map.width; ++col) {
            QPoint position(col, row);
            this->objects.append(
                new Sprite(QPixmap(":assets/grass.png"), position, -1, this->game));
            switch (map.map[row][col]) {
                case Tile::Player:
                    this->player =
                        new Sprite(QPixmap(":assets/pacman.png"), position, 10, this->game);
                    this->objects.append(this->player);
                    break;
                case Tile::Ghost: {
                    auto ghost = new Sprite(QPixmap(":assets/ghost.png"), position, 20, this->game);
                    this->objects.append(ghost);
                    this->ghosts.append(ghost);
                    break;
                }
                case Tile::Wall:
                    this->objects.append(
                        new Sprite(QPixmap(":assets/wall.png"), position, 0, this->game));
                    break;
                case Tile::Empty:
                    break;
                case Tile::Key: {
                    auto key = new Sprite(QPixmap(":assets/key.png"), position, 0, this->game);
                    this->objects.append(key);
                    this->keys.append(key);
                    break;
                }
                case Tile::Target:
                    this->objects.append(
                        new Sprite(QPixmap(":assets/target.png"), position, 0, this->game));
                    break;
            }
        }
    }

    // Draw walls around the map
    for (int row = -1; row <= map.height; row++) {
        this->objects.append(
            new Sprite(QPixmap(":assets/wall.png"), QPoint(-1, row), 0, this->game));
        this->objects.append(
            new Sprite(QPixmap(":assets/wall.png"), QPoint(map.width, row), 0, this->game));
    }
    for (int col = 0; col < map.width; col++) {
        this->objects.append(
            new Sprite(QPixmap(":assets/wall.png"), QPoint(col, -1), 0, this->game));
        this->objects.append(
            new Sprite(QPixmap(":assets/wall.png"), QPoint(col, map.height), 0, this->game));
    }

    // Add all objects to the scene
    for (auto object : this->objects) {
        this->gameScene->addItem(object);
    }

    // Fit scene to view
    this->view->fitInView(this->gameScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void BaseGamePage::clear() {
    // Stop timer
    this->timer->stop();
    // Delete all objects from game scene
    this->gameScene->clear();
    this->objects.clear();
    this->ghosts.clear();
    this->keys.clear();
}

void BaseGamePage::draw(GameInfo info) {
    // Update player position
    this->player->setPosition(QPoint(info.playerPosition.x, info.playerPosition.y));
    // Update ghost positions
    for (int i = 0; i < this->ghosts.size(); ++i) {
        this->ghosts[i]->setPosition(QPoint(info.ghostPositions[i].x, info.ghostPositions[i].y));
    }
    // Update key visibility
    for (auto& key : this->keys) {
        bool found = false;
        for (auto& keyInfo : info.keyPositions) {
            if (key->getPosition() == QPoint(keyInfo.x, keyInfo.y)) {
                found = true;
                break;
            }
        }
        key->setVisible(found);
    }
    // Update stats
    std::string step_text = "Step: " + std::to_string(info.step);
    std::string key_text = "Keys: " + std::to_string(info.totalKeys - info.keyPositions.size()) +
                           "/" + std::to_string(info.totalKeys);
    if (info.keyPositions.size() == 0) {
        this->keyText->setStyleSheet("QLabel { color : green; }");
    } else {
        this->keyText->setStyleSheet("QLabel { color : black; }");
    }
    this->stepText->setText(step_text.c_str());
    this->keyText->setText(key_text.c_str());
}

void BaseGamePage::tick() {}

BaseGamePage::~BaseGamePage() {}
