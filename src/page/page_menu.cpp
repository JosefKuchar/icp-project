#include "page_menu.hpp"
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "page.hpp"

MenuPage::MenuPage(QWidget* parent) : QWidget(parent) {
    // Add button
    QPushButton* button = new QPushButton("Start Game", this);
    button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    // Set page on button click
    connect(button, &QPushButton::clicked, [this]() {
        QStackedWidget* widget = (QStackedWidget*)this->parentWidget();
        widget->setCurrentIndex((int)Page::Play);
    });

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(button);
    this->setLayout(layout);
}

MenuPage::~MenuPage() {}
