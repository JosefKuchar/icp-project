#pragma once

#include <QtWidgets>

class Object : public QGraphicsPixmapItem {
   public:
    Object(const QPixmap& pixmap, QPoint position);
    void setPosition(QPoint position);
    QPoint getPosition();
    void update();
    ~Object();

   private:
    QVariantAnimation* m_animation;
    QPoint m_position;
    QPoint m_nextPosition;
};
