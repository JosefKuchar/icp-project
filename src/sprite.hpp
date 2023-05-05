/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file sprite.hpp
 * @brief Sprite header
 */

#pragma once

#include <QtWidgets>
#include "game/game.hpp"

class Sprite : public QGraphicsPixmapItem {
   public:
    Sprite(const QPixmap& pixmap, QPoint position, int zIndex, Game* game);
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
