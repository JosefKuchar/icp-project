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

PlayPage::PlayPage(QWidget* parent) : BaseGamePage(parent) {}

void PlayPage::showEvent([[maybe_unused]] QShowEvent* event) {
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    try {
        // Load map and start game
        MapInfo map = MapInfo(window->mapPath);
        this->drawMap(map);
        window->serializer.setMap(map);
        window->serializer.addStep(this->game->getGameInfo());
        this->timer->start(globals::TICK_RATE);
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

void PlayPage::end() {
    this->clear();
    // Go to end page
    QStackedWidget* stackedWidget = (QStackedWidget*)this->parentWidget();
    stackedWidget->setCurrentIndex((int)Page::End);
}

void PlayPage::tick() {
    // Tick game
    this->game->tick();
    // Get game info back from logic
    GameInfo info = this->game->getGameInfo();
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    // Add step to serializer
    window->serializer.addStep(info);
    // Check if game is over
    if (info.state != GameState::Playing) {
        window->lastTick = info;
        this->end();
        return;
    }
    // Draw step
    this->draw(info);
}

PlayPage::~PlayPage() {}
