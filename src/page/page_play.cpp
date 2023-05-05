/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_play.cpp
 * @brief PlayPage implementation
 */

#include "page_play.hpp"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "../mainwindow.hpp"
#include "globals.hpp"
#include "maploader.hpp"
#include "page.hpp"

PlayPage::PlayPage(QWidget* parent) : QWidget(parent) {}

void PlayPage::showEvent(QShowEvent* event) {
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    try {
        MapInfo map = MapInfo(window->mapPath);
        this->game = new Game(map);
        m_gameScene = new QGraphicsScene(this);

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

        this->start();
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

    QGraphicsView* view = new QGraphicsView(m_gameScene);

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    this->setLayout(layout);
    this->setFocusPolicy(Qt::StrongFocus);
}

void PlayPage::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            this->game->setDirection(Direction::Up);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            this->game->setDirection(Direction::Down);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            this->game->setDirection(Direction::Left);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            this->game->setDirection(Direction::Right);
            break;
    }
}

void PlayPage::start() {
    this->timer = new QTimer(this);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(tick()));
    this->timer->start(globals::TICK_RATE);
}

void PlayPage::tick() {
    this->game->tick();
    GameInfo info = this->game->getGameInfo();
    if (info.state != GameState::Playing) {
        // Stop timer
        this->timer->stop();
        // Go to end page
        QStackedWidget* stackedWidget = (QStackedWidget*)this->parentWidget();
        stackedWidget->setCurrentIndex((int)Page::End);
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

PlayPage::~PlayPage() {}
