/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_menu.cpp
 * @brief MenuPage implementation
 */

#include "page_menu.hpp"
#include <QFileDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include "../mainwindow.hpp"
#include "page.hpp"

MenuPage::MenuPage(QWidget* parent) : QWidget(parent) {
    // Play button
    QPushButton* playButton = new QPushButton("Start Game", this);
    playButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(playButton, &QPushButton::clicked, [this]() {
        // Open dialog to select map
        QFileDialog dialog(this, "Select Map", "");
        dialog.setFileMode(QFileDialog::ExistingFile);
        if (dialog.exec()) {
            // Set map path and initialize serializer
            auto filename = dialog.selectedFiles().first();
            QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
            MainWindow* mainWindow = (MainWindow*)widget->parentWidget();
            mainWindow->serializer.clearSteps();
            mainWindow->mapPath = filename.toStdString();
            // Go to play page
            widget->setCurrentIndex((int)Page::Play);
        }
    });

    // Replay button
    QPushButton* loadButton = new QPushButton("Load Replay", this);
    loadButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(loadButton, &QPushButton::clicked, [this]() {
        // Open dialog to select replay
        QFileDialog dialog(this, "Load Replay", "", "ICP Pacman (*.icpacman)");
        dialog.setFileMode(QFileDialog::ExistingFile);
        if (dialog.exec()) {
            // Load replay
            auto filename = dialog.selectedFiles().first();
            QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
            MainWindow* mainWindow = (MainWindow*)widget->parentWidget();
            {
                std::ifstream infile(filename.toStdString());
                boost::archive::text_iarchive archive2(infile);
                archive2 >> mainWindow->serializer;
            }
            // Go to replay page
            widget->setCurrentIndex((int)Page::Replay);
        }
    });

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(playButton);
    layout->addWidget(loadButton);
    this->setLayout(layout);
}

MenuPage::~MenuPage() {}
