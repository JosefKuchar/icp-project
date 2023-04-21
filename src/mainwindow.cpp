#include "mainwindow.hpp"
#include <iostream>
#include "game/direction.hpp"
#include "game_scene.hpp"
#include "globals.hpp"
#include "maploader.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // This is needed to get arrow keys to work for some reason
    this->setFocusPolicy(Qt::StrongFocus);

    MapInfo map = MapInfo("./examples/intro.txt");
    m_gameScene = new GameScene(map);
    ui->graphicsView->setScene(m_gameScene);
    ui->graphicsView->show();
    m_gameScene->start();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
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

MainWindow::~MainWindow() {
    delete ui;
}
