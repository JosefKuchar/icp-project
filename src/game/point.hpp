#pragma once

#include "direction.hpp"

class Point {
   public:
    int x;
    int y;

    Point();
    Point (int x, int y);
    Point operator+ (Point);
    Point operator+ (Direction);
    Point operator+= (Direction);
    bool operator== (Point);
};
