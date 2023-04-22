#pragma once

#include <QtWidgets>
#include "game/game.hpp"

class Sprite : public QGraphicsPixmapItem {
   public:
    Sprite(const QPixmap& pixmap, QPoint position, Game* game);
    void setPosition(QPoint position);
    QPoint getPosition();
    void update();
    ~Sprite();
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

   private:
    QVariantAnimation* m_animation;
    QPoint m_position;
    QPoint m_nextPosition;
    Game* m_game;
};