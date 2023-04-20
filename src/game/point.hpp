#pragma once

#include "direction.hpp"

#include <cstddef>
#include <functional>

class Point {
   public:
    int x;
    int y;

    Point();
    Point (int x, int y);
    Point operator+ (Point);
    Point operator+ (Direction);
    Point operator+= (Direction);
    bool operator== (const Point&) const;
};

template<> struct std::hash<Point> {
    std::size_t operator()(const Point& point) const {
        return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
    }
};
