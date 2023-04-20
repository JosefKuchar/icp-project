#include "pacman.hpp"

Pacman::Pacman(QPoint position) : Object(QPixmap(":assets/pacman.png"), position) {
    // Make sure pacman is always on top
    this->setZValue(10);
}
