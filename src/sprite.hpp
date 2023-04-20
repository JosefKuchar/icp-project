#pragma once

#include <QtWidgets>

class Sprite : public QGraphicsPixmapItem {
   public:
    Sprite(const QPixmap& pixmap, QPoint position);
    void setPosition(QPoint position);
    QPoint getPosition();
    void update();
    ~Sprite();

   private:
    QVariantAnimation* m_animation;
    QPoint m_position;
    QPoint m_nextPosition;
};
