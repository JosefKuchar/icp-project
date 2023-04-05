#include "object.hpp"
#include <iostream>
#include "globals.hpp"

Object::Object(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap) {
    m_animation = new QVariantAnimation();
    m_animation->setEasingCurve(QEasingCurve::InOutCubic);
    m_animation->setDuration(globals::ANIMATION_DURATION);
    QObject::connect(m_animation, &QVariantAnimation::valueChanged,
                     [this](const QVariant& value) { this->setPos(value.toPointF()); });
    m_x = 0;
    m_y = 0;
    m_nextX = 0;
    m_nextY = 0;
}

void Object::setPosition(int x, int y) {
    // Next is now current position
    m_x = m_nextX;
    m_y = m_nextY;
    // Set next position
    m_nextX = x;
    m_nextY = y;
    // Setup animation from current position to next position
    auto pixmap = this->pixmap();
    m_animation->setStartValue(this->pos());
    m_animation->setEndValue(QPointF(pixmap.width() * m_nextX, pixmap.height() * m_nextY));
    // Start animation
    m_animation->start();
}

QPoint Object::getPosition() {
    return QPoint(m_nextX, m_nextY);
}

Object::~Object() {
    delete m_animation;
}
