#pragma once
#include "Point.hpp"
#include "Triangle.hpp"
#include <vector>

class AABB {
    public:
        Point minAABB, maxAABB;
        AABB() {}
        AABB(const Point& minAABB, const Point& maxAABB) : minAABB(minAABB), maxAABB(maxAABB) {}
        Point center() const;
        AABB makeUniCube() const;
        //AABBvsAABB
        AABB fromTriangle(const Triangle& tri) const;
        bool overlaps(const AABB& other) const;
        bool isIntersect(const Triangle& tri) const;
        //SAT
        bool isIntersectSAT(const Triangle& tri) const;
};