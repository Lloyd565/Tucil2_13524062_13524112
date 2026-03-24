#pragma once
#include "Point.hpp"

class Triangle {
    public:
        Point v0, v1, v2;
        Triangle() {}
        Triangle(const Point& v0, const Point& v1, const Point& v2) : v0(v0), v1(v1), v2(v2) {}
};
