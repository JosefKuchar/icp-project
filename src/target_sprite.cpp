#include "target_sprite.hpp"

TargetSprite::TargetSprite(QPoint position, Game* game) : Sprite(QPixmap(":assets/target.png"), position, game) {}
