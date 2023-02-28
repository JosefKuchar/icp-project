#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <iostream>

class Sprite : public QGraphicsPixmapItem {
   public:
    Sprite(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap) {}
};

class Grid : public QGraphicsScene {
   public:
    Grid(int rows, int cols, const QPixmap& spritePixmap)
        : m_rows(rows), m_cols(cols), m_spritePixmap(spritePixmap) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                Sprite* sprite = new Sprite(m_spritePixmap);
                std::cout << m_spritePixmap.width() << std::endl;
                ;
                sprite->setPos(col * (m_spritePixmap.width() + 5),
                               row * (m_spritePixmap.height() + 5));
                addItem(sprite);
            }
        }
    }

   private:
    int m_rows;
    int m_cols;
    QPixmap m_spritePixmap;
};

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QPixmap spritePixmap("sprite.png");
    if (spritePixmap.isNull())
        std::cout << "darn" << std::endl;
    else
        std::cout << "not null" << std::endl;
    Grid grid(10, 10, spritePixmap);
    QGraphicsView view(&grid);
    view.show();

    MainWindow w;
    w.show();
    return a.exec();
}
