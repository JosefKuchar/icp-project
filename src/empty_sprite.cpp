#include "empty_sprite.hpp"

EmptySprite::EmptySprite(QPoint position, Game* game)
        : Sprite(QPixmap(":assets/grass.png"), position, game) {
    this->setZValue(-10);
}
