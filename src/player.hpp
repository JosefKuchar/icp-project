#pragma once

#include <QtWidgets>

class Player : public QGraphicsPixmapItem {
   public:
    Player(const QPixmap& pixmap);
    void setPosition(int x, int y);
    void update();
    ~Player();

   private:
    QVariantAnimation* m_animation;
    int m_x;
    int m_y;
    int m_nextX;
    int m_nextY;
};
