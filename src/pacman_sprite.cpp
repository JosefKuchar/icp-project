#include "pacman_sprite.hpp"

PacmanSprite::PacmanSprite(QPoint position, Game* game)
    : Sprite(QPixmap(":assets/pacman.png"), position, game) {
    // Make sure pacman is always on top
    this->setZValue(10);
}
