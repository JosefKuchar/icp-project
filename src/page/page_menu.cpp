#include "page_menu.hpp"
#include <QFileDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <iostream>
#include "page.hpp"

MenuPage::MenuPage(QWidget* parent) : QWidget(parent) {
    // Add button
    QPushButton* playButton = new QPushButton("Start Game", this);
    playButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    // Set page on button click
    connect(playButton, &QPushButton::clicked, [this]() {
        // Open dialog to select map
        QFileDialog dialog(this, "Select Map", "");
        dialog.setFileMode(QFileDialog::ExistingFile);
        if (dialog.exec()) {
            auto filename = dialog.selectedFiles().first();
            std::cout << filename.toStdString() << std::endl;
            // TODO Load map
            QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
            widget->setCurrentIndex((int)Page::Play);
        }
    });

    QPushButton* loadButton = new QPushButton("Load Replay", this);
    loadButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(loadButton, &QPushButton::clicked, [this]() {
        QFileDialog dialog(this, "Load Replay", "", "ICP Pacman (*.icpacman)");
        dialog.setFileMode(QFileDialog::ExistingFile);
        if (dialog.exec()) {
            auto filename = dialog.selectedFiles().first();
            std::cout << filename.toStdString() << std::endl;
            // TODO Load replay
        }
    });

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(playButton);
    layout->addWidget(loadButton);
    this->setLayout(layout);
}

MenuPage::~MenuPage() {}
