#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include "game_scene.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    std::string mapPath;

   private:
    QStackedWidget* stackedWidget;
};
