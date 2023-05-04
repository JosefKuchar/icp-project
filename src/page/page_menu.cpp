#include "page_menu.hpp"
#include <QFileDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <iostream>
#include "page.hpp"

MenuPage::MenuPage(QWidget* parent) : QWidget(parent) {
    // Add button
    QPushButton* button = new QPushButton("Start Game", this);
    button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    // Set page on button click
    connect(button, &QPushButton::clicked, [this]() {
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

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(button);
    this->setLayout(layout);
}

MenuPage::~MenuPage() {}
