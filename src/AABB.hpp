#pragma once
#include "Point.hpp"
#include "Triangle.hpp"
#include <vector>
using namespace std;

class AABB {
    public:
        Point minAABB, maxAABB;
        Point center() const;
        AABB() {}
        AABB(const Point& minAABB, const Point& maxAABB) : minAABB(minAABB), maxAABB(maxAABB) {}
        ~AABB()=default;
        AABB makeUniCube() const;
        bool isIntersect(const Triangle& tri) const;
};