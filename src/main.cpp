#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // MapInfo map = MapInfo("./examples/intro.txt");

    // Grid grid(map);
    // QGraphicsView view(&grid);
    // view.show();

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
