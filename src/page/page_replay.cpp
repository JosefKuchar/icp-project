/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_play.cpp
 * @brief PlayPage implementation
 */

#include "page_replay.hpp"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <iostream>
#include "../mainwindow.hpp"
#include "globals.hpp"
#include "maploader.hpp"
#include "page.hpp"

ReplayPage::ReplayPage(QWidget* parent) : QWidget(parent) {
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_gameScene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(m_gameScene);

    QPushButton* playBackwards = new QPushButton("Play backwards", this);
    playBackwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(playBackwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Backwards;
        this->timer->start(globals::TICK_RATE);
    });

    QPushButton* stepBackwards = new QPushButton("Step backwards", this);
    stepBackwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(stepBackwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Stopped;
        this->timer->stop();
        if (this->frameIndex > 0) {
            this->frameIndex--;
        }
        this->draw();
    });

    QPushButton* stop = new QPushButton("Stop", this);
    stop->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(stop, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Stopped;
        this->timer->stop();
    });

    QPushButton* stepForwards = new QPushButton("Step forwards", this);
    stepForwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(stepForwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Stopped;
        this->timer->stop();
        MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
        if (this->frameIndex < window->serializer.ticks.size() - 1) {
            this->frameIndex++;
        }
        this->draw();
    });

    QPushButton* playForwards = new QPushButton("Play forwards", this);
    playForwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(playForwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Forwards;
        this->timer->start(globals::TICK_RATE);
    });

    layout->addWidget(view);
    layout->addWidget(playBackwards);
    layout->addWidget(stepBackwards);
    layout->addWidget(stop);
    layout->addWidget(stepForwards);
    layout->addWidget(playForwards);

    this->setLayout(layout);
    this->setFocusPolicy(Qt::StrongFocus);
}

void ReplayPage::showEvent(QShowEvent* event) {
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    try {
        MapInfo map = window->serializer.map;
        this->game = new Game(map);

        // Create all objects
        for (int row = 0; row < map.height; ++row) {
            for (int col = 0; col < map.width; ++col) {
                QPoint position(col, row);
                m_objects.append(
                    new Sprite(QPixmap(":assets/grass.png"), position, -1, this->game));
                switch (map.map[row][col]) {
                    case Tile::Player:
                        m_player =
                            new Sprite(QPixmap(":assets/pacman.png"), position, 10, this->game);
                        m_objects.append(m_player);
                        break;
                    case Tile::Ghost: {
                        auto ghost =
                            new Sprite(QPixmap(":assets/ghost.png"), position, 20, this->game);
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
            m_objects.append(
                new Sprite(QPixmap(":assets/wall.png"), QPoint(-1, row), 0, this->game));
            m_objects.append(
                new Sprite(QPixmap(":assets/wall.png"), QPoint(map.width, row), 0, this->game));
        }
        for (int col = 0; col < map.width; col++) {
            m_objects.append(
                new Sprite(QPixmap(":assets/wall.png"), QPoint(col, -1), 0, this->game));
            m_objects.append(
                new Sprite(QPixmap(":assets/wall.png"), QPoint(col, map.height), 0, this->game));
        }

        // Add all objects to the scene
        for (auto object : m_objects) {
            m_gameScene->addItem(object);
        }
    } catch (std::exception& e) {
        // Show error dialog
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Error loading map");
        msgBox.exec();
        // Go back to menu
        QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
        widget->setCurrentIndex((int)Page::Menu);
        return;
    }
}

void ReplayPage::end() {
    // Stop timer
    this->timer->stop();
    // Delete all objects from game scene
    this->m_gameScene->clear();
    this->m_objects.clear();
    this->m_ghosts.clear();
    this->m_keys.clear();
    // Go to end page
    QStackedWidget* stackedWidget = (QStackedWidget*)this->parentWidget();
    stackedWidget->setCurrentIndex((int)Page::End);
}

void ReplayPage::tick() {
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    switch (this->replayMode) {
        case ReplayMode::Stopped:
            break;
        case ReplayMode::Forwards:
            if (this->frameIndex < window->serializer.ticks.size() - 1) {
                this->frameIndex++;
            }
            break;
        case ReplayMode::Backwards:
            if (this->frameIndex > 0) {
                this->frameIndex--;
            }
            break;
    }
    this->draw();
}

void ReplayPage::draw() {
    std::cout << this->frameIndex << std::endl;
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    GameInfo info = window->serializer.getStep(this->frameIndex);
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

ReplayPage::~ReplayPage() {}
