#include "point.hpp"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
};

Point Point::operator+(Point point) {
    return Point(this->x + point.x, this->y + point.y);
};

Point Point::operator+(Direction direction) {
    switch (direction) {
        case Direction::Up:
            return Point(this->x, this->y - 1);
        case Direction::Down:
            return Point(this->x, this->y + 1);
        case Direction::Left:
            return Point(this->x - 1, this->y);
        case Direction::Right:
            return Point(this->x + 1, this->y);
    }
};

Point Point::operator+=(Direction direction) {
    switch (direction) {
        case Direction::Up:
            this->y -= 1;
            break;
        case Direction::Down:
            this->y += 1;
            break;
        case Direction::Left:
            this->x -= 1;
            break;
        case Direction::Right:
            this->x += 1;
            break;
    }
    return *this;
};

bool Point::operator==(Point point) {
    return this->x == point.x && this->y == point.y;
};