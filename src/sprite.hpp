/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file sprite.hpp
 * @brief Sprite header
 */

#pragma once

#include <QtWidgets>
#include "game/game.hpp"

/**
 * @brief Movable object in game with built-in animation
 */
class Sprite : public QGraphicsPixmapItem {
   public:
    /**
     * @brief Sprite constructor
     * @param pixmap Sprite pixmap
     * @param position Initial sprite position
     * @param zIndex Z-index of sprite
     * @param game Game logic reference
     */
    Sprite(const QPixmap& pixmap, QPoint position, int zIndex, Game* game);
    ~Sprite();

    /**
     * @brief Set sprite position
     * @param position New position
     * Animation is started from current position to new position
     */
    void setPosition(QPoint position);

    /**
     * @brief Get sprite position
     * @return Current position
     */
    QPoint getPosition();

    /**
     * @brief Mouse press event
     * @param event Mouse event
     * When sprite is clicked, it sets target position in game
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

   private:
    /// Animation
    QVariantAnimation* animation;
    /// Current position
    QPoint position;
    /// Next position
    QPoint nextPosition;
    /// Game logic reference
    Game* game;
};
