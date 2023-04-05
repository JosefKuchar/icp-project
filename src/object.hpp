#pragma once

#include <QtWidgets>

class Object : public QGraphicsPixmapItem {
   public:
    Object(const QPixmap& pixmap);
    void setPosition(int x, int y);
    QPoint getPosition();
    void update();
    ~Object();

   private:
    QVariantAnimation* m_animation;
    int m_x;
    int m_y;
    int m_nextX;
    int m_nextY;
};
