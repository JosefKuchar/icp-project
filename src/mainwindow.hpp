/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file mainwindow.hpp
 * @brief Main window header
 */

#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QStackedWidget>
#include "serializer.hpp"

/**
 * @brief Main window
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    /**
     * @brief Construct a new Main Window object
     * @param parent Parent widget
     */
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    /// Path to map file
    std::string mapPath;
    /// Object for replays
    Serializer serializer;

   private:
    QStackedWidget* stackedWidget;
};
