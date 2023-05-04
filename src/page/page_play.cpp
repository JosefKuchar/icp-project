#include "page_play.hpp"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "../mainwindow.hpp"
#include "maploader.hpp"

PlayPage::PlayPage(QWidget* parent) : QWidget(parent) {}

void PlayPage::showEvent(QShowEvent* event) {
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    MapInfo map = MapInfo(window->mapPath);
    m_gameScene = new GameScene(map);
    m_gameScene->start();

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
            this->m_gameScene->game->setDirection(Direction::Up);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            this->m_gameScene->game->setDirection(Direction::Down);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            this->m_gameScene->game->setDirection(Direction::Left);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            this->m_gameScene->game->setDirection(Direction::Right);
            break;
    }
}

PlayPage::~PlayPage() {}
