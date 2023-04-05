#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // QTimer timer;
    // QObject::connect(&timer, &QTimer::timeout, [&]() {
    //     grid.updatePositions();
    //     view.update();
    // });
    // timer.start(16);

    MainWindow w;
    w.show();
    return a.exec();
}
