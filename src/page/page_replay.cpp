/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_replay.cpp
 * @brief ReplayPage implementation
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

ReplayPage::ReplayPage(QWidget* parent) : BaseGamePage(parent) {
    // Create button layout
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Play backwards button
    QPushButton* playBackwards = new QPushButton("Play backwards", this);
    playBackwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(playBackwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Backwards;
        this->timer->start(globals::TICK_RATE);
    });

    // Step backwards button
    QPushButton* stepBackwards = new QPushButton("Step backwards", this);
    stepBackwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(stepBackwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Stopped;
        this->timer->stop();
        if (this->frameIndex > 0) {
            this->frameIndex--;
        }
        this->getStepAndDraw();
    });

    // Stop button
    QPushButton* stop = new QPushButton("Stop", this);
    stop->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(stop, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Stopped;
        this->timer->stop();
    });

    // Step forwards button
    QPushButton* stepForwards = new QPushButton("Step forwards", this);
    stepForwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(stepForwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Stopped;
        this->timer->stop();
        MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
        if (this->frameIndex < window->serializer.getStepsCount() - 1) {
            this->frameIndex++;
        }
        this->getStepAndDraw();
    });

    // Play forwards button
    QPushButton* playForwards = new QPushButton("Play forwards", this);
    playForwards->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(playForwards, &QPushButton::clicked, [this]() {
        this->replayMode = ReplayMode::Forwards;
        this->timer->start(globals::TICK_RATE);
    });

    // Back to menu button
    QPushButton* backMenu = new QPushButton("Back to menu", this);
    backMenu->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(backMenu, &QPushButton::clicked, [this]() {
        this->clear();
        this->frameIndex = 0;
        this->replayMode = ReplayMode::Stopped;
        QStackedWidget* stackedWidget = (QStackedWidget*)this->parentWidget();
        stackedWidget->setCurrentIndex((int)Page::Menu);
    });

    // Add buttons to button layout
    buttonLayout->addWidget(playBackwards);
    buttonLayout->addWidget(stepBackwards);
    buttonLayout->addWidget(stop);
    buttonLayout->addWidget(stepForwards);
    buttonLayout->addWidget(playForwards);
    buttonLayout->addWidget(backMenu);

    // Add button layout to main layout
    this->layout->addLayout(buttonLayout);

    // Set default values
    this->frameIndex = 0;
    this->replayMode = ReplayMode::Stopped;
}

void ReplayPage::showEvent([[maybe_unused]] QShowEvent* event) {
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    try {
        MapInfo map = window->serializer.getMap();
        this->game = new Game(map);
        this->drawMap(map);
        this->getStepAndDraw();
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

void ReplayPage::tick() {
    // Update frame index
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    switch (this->replayMode) {
        case ReplayMode::Stopped:
            break;
        case ReplayMode::Forwards:
            if (this->frameIndex < window->serializer.getStepsCount() - 1) {
                this->frameIndex++;
            }
            break;
        case ReplayMode::Backwards:
            if (this->frameIndex > 0) {
                this->frameIndex--;
            }
            break;
    }
    // Draw step
    this->getStepAndDraw();
}

void ReplayPage::getStepAndDraw() {
    // Fetch step from serializer
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    GameInfo info = window->serializer.getStep(this->frameIndex);
    // Draw step
    this->draw(info);
}

ReplayPage::~ReplayPage() {}
