/**
 * @author Josef Kuchař <xkucha28@stud.fit.vutbr.cz>
 * @author Matej Sirovatka <xsirov00@stud.fit.vutbr.cz>
 * @file sprite.cpp
 * @brief Sprite implementation
 */

#include "sprite.hpp"
#include <iostream>
#include "globals.hpp"

Sprite::Sprite(const QPixmap& pixmap, QPoint position, int zIndex, Game* game)
    : QGraphicsPixmapItem(pixmap) {
    this->game = game;
    // Set inital position
    this->position = position;
    this->nextPosition = position;
    this->setPos(pixmap.width() * this->position.x(), pixmap.height() * this->position.y());
    // Set z-index
    this->setZValue(zIndex);
    // Setup animation
    this->animation = new QVariantAnimation();
    this->animation->setEasingCurve(QEasingCurve::InOutCubic);
    this->animation->setDuration(globals::ANIMATION_DURATION);
    QObject::connect(this->animation, &QVariantAnimation::valueChanged,
                     [this](const QVariant& value) { this->setPos(value.toPointF()); });
}

void Sprite::setPosition(QPoint position) {
    // Next is now current position
    this->position = this->nextPosition;
    // Set next position
    this->nextPosition = position;
    // Setup animation from current position to next position
    auto pixmap = this->pixmap();
    this->animation->setStartValue(this->pos());
    this->animation->setEndValue(
        QPointF(pixmap.width() * this->nextPosition.x(), pixmap.height() * this->nextPosition.y()));
    // Start animation
    this->animation->start();
}

void Sprite::mousePressEvent([[maybe_unused]] QGraphicsSceneMouseEvent* event) {
    this->game->setTargetPosition(Point(this->nextPosition.x(), this->nextPosition.y()));
}

QPoint Sprite::getPosition() {
    return this->nextPosition;
}

Sprite::~Sprite() {
    delete this->animation;
}
