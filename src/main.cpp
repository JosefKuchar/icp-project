/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file main.cpp
 * @brief Main file
 */

#include <QApplication>
#include "mainwindow.hpp"

/**
 * @brief Entry point
 * @param argc Number of arguments
 * @param arv Array of arguments
 */
int main(int argc, char* argv[]) {
    // Create application
    QApplication a(argc, argv);
    // Create main window
    MainWindow w;
    // Show main window
    w.show();
    // Run application
    return a.exec();
}
