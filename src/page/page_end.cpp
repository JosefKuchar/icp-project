#include "page_end.hpp"
#include <QFileDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include "../mainwindow.hpp"
#include "boost/archive/text_oarchive.hpp"
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
            MainWindow* window = (MainWindow*)this->parentWidget()->parentWidget();
            auto filename = dialog.selectedFiles().first();
            std::ofstream outfile(filename.toStdString());
            boost::archive::text_oarchive archive(outfile);
            archive << window->serializer;
        }
    });

    // Add to layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(backButton);
    layout->addWidget(saveButton);
    this->setLayout(layout);
}

EndPage::~EndPage() {}
