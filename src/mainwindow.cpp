/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file mainwindow.cpp
 * @brief Main window implementation
 */

#include "mainwindow.hpp"
#include "page/page_end.hpp"
#include "page/page_menu.hpp"
#include "page/page_play.hpp"
#include "page/page_replay.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    // Create stacked widget
    this->stackedWidget = new QStackedWidget(this);
    // Create pages
    MenuPage* menuPage = new MenuPage(this);
    PlayPage* playPage = new PlayPage(this);
    ReplayPage* replayPage = new ReplayPage(this);
    EndPage* endPage = new EndPage(this);
    // Add pages to stacked widget
    this->stackedWidget->addWidget(menuPage);
    this->stackedWidget->addWidget(playPage);
    this->stackedWidget->addWidget(replayPage);
    this->stackedWidget->addWidget(endPage);
    // Set stacked widget as central widget
    this->setCentralWidget(this->stackedWidget);
    this->setGeometry(0, 0, 800, 600);
}

MainWindow::~MainWindow() {}
