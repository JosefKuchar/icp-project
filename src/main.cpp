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
                sprite->setPos(col * (m_spritePixmap.width() + 5),
                               row * (m_spritePixmap.height() + 5));
                addItem(sprite);
                m_sprites.append(sprite);
            }
        }
    }

    void updatePositions() {
        for (auto sprite : m_sprites) {
            QPointF pos = sprite->pos();
            pos.setX(pos.x() + 1.0f);  // Update the x position of the sprite
            sprite->setPos(pos);
        }
    }

   private:
    int m_rows;
    int m_cols;
    QPixmap m_spritePixmap;
    QList<Sprite*> m_sprites;
};

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QPixmap spritePixmap(":sprite.png");
    Grid grid(10, 10, spritePixmap);
    QGraphicsView view(&grid);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        grid.updatePositions();
        view.update();
    });
    timer.start(16);

    // MainWindow w;
    // w.show();
    return a.exec();
}
