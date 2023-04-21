#include "ghost_sprite.hpp"

GhostSprite::GhostSprite(QPoint position, Game* game)
    : Sprite(QPixmap(":assets/ghost.png"), position, game) {}
