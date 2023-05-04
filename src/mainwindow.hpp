#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>
#include "serializer.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    std::string mapPath;
    Serializer serializer;

   private:
    QStackedWidget* stackedWidget;
};
