#include "player.hpp"

Player::Player(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap) {
    m_animation = new QVariantAnimation();
    m_animation->setDuration(1000);
    m_animation->setStartValue(QPointF(0, 0));
    m_animation->setEndValue(QPointF(100, 100));
    QObject::connect(m_animation, &QVariantAnimation::valueChanged,
                     [this](const QVariant& value) { this->setPos(value.toPointF()); });
    m_animation->start();
}

void Player::setPosition(int x, int y) {
    m_animation->setStartValue(this->pos());
    m_animation->setEndValue(QPointF(x, y));
}

Player::~Player() {
    delete m_animation;
}
