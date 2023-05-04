#include "mainwindow.hpp"
#include <iostream>
#include "page/page_end.hpp"
#include "page/page_menu.hpp"
#include "page/page_play.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->stackedWidget = new QStackedWidget(this);
    MenuPage* menuPage = new MenuPage(this);
    PlayPage* playPage = new PlayPage(this);
    EndPage* endPage = new EndPage(this);
    this->stackedWidget->addWidget(menuPage);
    this->stackedWidget->addWidget(playPage);
    this->stackedWidget->addWidget(endPage);
    this->setCentralWidget(this->stackedWidget);
}

MainWindow::~MainWindow() {}
