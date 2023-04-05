#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void keyPressEvent(QKeyEvent* event) override;

   private:
    Ui::MainWindow* ui;
    Grid* m_grid;
};
#endif  // MAINWINDOW_H
