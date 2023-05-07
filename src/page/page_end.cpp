/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file page_end.cpp
 * @brief EndPage implementation
 */

#include "page_end.hpp"
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include "../game/game.hpp"
#include "../mainwindow.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "page.hpp"

EndPage::EndPage(QWidget* parent) : QWidget(parent) {
    // Create labels
    this->resultText = new QLabel(this);
    this->stepText = new QLabel(this);
    this->keyText = new QLabel(this);
    this->resultText->setAlignment(Qt::AlignCenter);
    this->stepText->setAlignment(Qt::AlignCenter);
    this->keyText->setAlignment(Qt::AlignCenter);

    // Back button
    QPushButton* backButton = new QPushButton("Back to Menu", this);
    backButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(backButton, &QPushButton::clicked, [this]() {
        QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
        widget->setCurrentIndex((int)Page::Menu);
    });
    // Save button
    QPushButton* saveButton = new QPushButton("Save Replay", this);
    saveButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(saveButton, &QPushButton::clicked, [this]() {
        // Open dialog
        QFileDialog dialog(this, "Save Replay", "", "ICP Pacman (*.icpacman)");
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setDefaultSuffix(".icpacman");
        if (dialog.exec()) {
            // Save replay
            MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
            auto filename = dialog.selectedFiles().first();
            std::ofstream outfile(filename.toStdString());
            boost::archive::text_oarchive archive(outfile);
            archive << window->serializer;
        }
    });

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* scoreLayout = new QHBoxLayout(this);
    layout->addWidget(this->resultText);
    scoreLayout->addWidget(this->stepText);
    scoreLayout->addWidget(this->keyText);
    layout->addLayout(scoreLayout);
    layout->addWidget(backButton);
    layout->addWidget(saveButton);
    this->setLayout(layout);
}

void EndPage::showEvent([[maybe_unused]] QShowEvent* event) {
    // Fetch info
    MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
    GameInfo info = window->lastTick;

    // Result text
    if (info.state == GameState::Won) {
        this->resultText->setText("You won!");
        this->resultText->setStyleSheet(
            "QLabel { font-size: 30px; font-weight: bold; color: green; } ");
    } else if (info.state == GameState::Lost) {
        this->resultText->setText("You lost!");
        this->resultText->setStyleSheet(
            "QLabel { font-size: 30px; font-weight: bold; color: red; } ");
    }

    // Other texts
    std::string stepsText = "Steps: " + std::to_string(info.step);
    std::string keysText = "Keys: " + std::to_string(info.totalKeys - info.keyPositions.size()) +
                           "/" + std::to_string(info.totalKeys);

    this->stepText->setText(QString::fromStdString(stepsText));
    this->keyText->setText(QString::fromStdString(keysText));

    const char* styleSheet = "QLabel { font-size: 20px; font-weight: bold; color: black; } ";
    this->stepText->setStyleSheet(styleSheet);
    this->keyText->setStyleSheet(styleSheet);
}

EndPage::~EndPage() {}
