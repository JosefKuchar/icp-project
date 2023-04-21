#include "key_sprite.hpp"

KeySprite::KeySprite(QPoint position, Game* game)
    : Sprite(QPixmap(":assets/key.png"), position, game) {}
