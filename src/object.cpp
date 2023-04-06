#include "object.hpp"
#include <iostream>
#include "globals.hpp"

Object::Object(const QPixmap& pixmap, QPoint position) : QGraphicsPixmapItem(pixmap) {
    // Set inital position
    m_position = position;
    m_nextPosition = position;
    this->setPos(pixmap.width() * m_position.x(), pixmap.height() * m_position.y());
    // Setup animation
    m_animation = new QVariantAnimation();
    m_animation->setEasingCurve(QEasingCurve::InOutCubic);
    m_animation->setDuration(globals::ANIMATION_DURATION);
    QObject::connect(m_animation, &QVariantAnimation::valueChanged,
                     [this](const QVariant& value) { this->setPos(value.toPointF()); });
}

void Object::setPosition(QPoint position) {
    // Next is now current position
    m_position = m_nextPosition;
    // Set next position
    m_nextPosition = position;
    // Setup animation from current position to next position
    auto pixmap = this->pixmap();
    m_animation->setStartValue(this->pos());
    m_animation->setEndValue(
        QPointF(pixmap.width() * m_nextPosition.x(), pixmap.height() * m_nextPosition.y()));
    // Start animation
    m_animation->start();
}

QPoint Object::getPosition() {
    return m_nextPosition;
}

Object::~Object() {
    delete m_animation;
}
