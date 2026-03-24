#pragma once
#include "Point.hpp"
#include "Triangle.hpp"
#include <bits/stdc++.h>
using namespace std;

class AABB {
    public:
        Point min, max;
        AABB() {}
        AABB(const Point& min, const Point& max) : min(min), max(max) {}

        // Center AABBnya
        Point center() const {
            return Point(
                (min.x + max.x) * 0.5,
                (min.y + max.y) * 0.5,
                (min.z + max.z) * 0.5
            );
        }

        AABB makeCube() const {
            double dx = max.x - min.x;
            double dy = max.y - min.y;
            double dz = max.z - min.z;
            double sref = std::max({dx, dy, dz});
            Point c = center();
            double h = sref * 0.5;
            return AABB(
                Point(c.x - h, c.y - h, c.z - h),
                Point(c.x + h, c.y + h, c.z + h)
            );
        }

        static AABB fromPoints(const vector<Point>& pts) {
            double minX = pts[0].x, minY = pts[0].y, minZ = pts[0].z;
            double maxX = pts[0].x, maxY = pts[0].y, maxZ = pts[0].z;
            for (const auto& p : pts) {
                minX = std::min(minX, p.x);  minY = std::min(minY, p.y);  minZ = std::min(minZ, p.z);
                maxX = std::max(maxX, p.x);  maxY = std::max(maxY, p.y);  maxZ = std::max(maxZ, p.z);
            }
            return AABB(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
        }

        bool intersectsTriangle(const Triangle& tri) const;
};