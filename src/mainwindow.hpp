#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include "game_scene.hpp"
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
