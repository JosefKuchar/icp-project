#pragma once

#include "direction.hpp"

#include <cstddef>
#include <functional>

#include "boost_libs/boost/archive/text_iarchive.hpp"
#include "boost_libs/boost/archive/text_oarchive.hpp"

class Point {
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &a, const unsigned version) {
            a & x & y;
        };

    public:
        int x;
        int y;

        Point();
        Point (int x, int y);
        Point operator+ (Point);
        Point operator+ (Direction);
        Point operator+= (Direction);
        bool operator== (const Point&) const;
        bool operator< (const Point&) const;
};

template<> struct std::hash<Point> {
    std::size_t operator()(const Point& point) const {
        return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
    }
};
