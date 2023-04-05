#include "mainwindow.hpp"
#include <iostream>
#include "game_scene.hpp"
#include "maploader.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // This is needed to get arrow keys to work for some reason
    this->setFocusPolicy(Qt::StrongFocus);

    MapInfo map = MapInfo("./examples/intro.txt");
    Grid* grid = new Grid(map);
    ui->graphicsView->setScene(grid);
    ui->graphicsView->show();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        // Arrows
        case Qt::Key_Up:
            std::cout << "Up" << std::endl;
            break;
        case Qt::Key_Down:
            std::cout << "Down" << std::endl;
            break;
        case Qt::Key_Left:
            std::cout << "Left" << std::endl;
            break;
        case Qt::Key_Right:
            std::cout << "Right" << std::endl;
            break;
        // WASD
        case Qt::Key_W:
            std::cout << "Up" << std::endl;
            break;
        case Qt::Key_A:
            std::cout << "Left" << std::endl;
            break;
        case Qt::Key_S:
            std::cout << "Down" << std::endl;
            break;
        case Qt::Key_D:
            std::cout << "Right" << std::endl;
            break;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
