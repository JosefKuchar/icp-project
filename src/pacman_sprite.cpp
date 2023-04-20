#include "pacman_sprite.hpp"

PacmanSprite::PacmanSprite(QPoint position) : Sprite(QPixmap(":assets/pacman.png"), position) {
    // Make sure pacman is always on top
    this->setZValue(10);
}
