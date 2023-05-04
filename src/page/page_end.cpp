#include "page_end.hpp"
#include <QFileDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <iostream>
#include "page.hpp"

EndPage::EndPage(QWidget* parent) : QWidget(parent) {
    // Add button
    QPushButton* backButton = new QPushButton("Back to Menu", this);
    backButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    // Set page on button click
    connect(backButton, &QPushButton::clicked, [this]() {
        QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
        widget->setCurrentIndex((int)Page::Menu);
    });
    QPushButton* saveButton = new QPushButton("Save Replay", this);
    saveButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    // Open save dialog on button click
    connect(saveButton, &QPushButton::clicked, [this]() {
        QFileDialog dialog(this, "Save Replay", "", "ICP Pacman (*.icpacman)");
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setDefaultSuffix(".icpacman");
        if (dialog.exec()) {
            auto filename = dialog.selectedFiles().first();
            // TODO Save
        }
    });

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(backButton);
    this->setLayout(layout);
}

EndPage::~EndPage() {}
