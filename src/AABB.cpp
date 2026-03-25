#include "AABB.hpp"
#include <bits/stdc++.h>

Point AABB::center() const {
    return Point((minAABB.x + maxAABB.x)/2,(minAABB.y + maxAABB.y)/2,(minAABB.z + maxAABB.z)/2);
}

AABB AABB::makeUniCube() const {
    double dx = maxAABB.x - minAABB.x;
    double dy = maxAABB.y - minAABB.y;
    double dz = maxAABB.z - minAABB.z;
    double sref = max({dx, dy, dz});
    Point c = center();
    double h = sref * 0.5;
    return AABB(
        Point(c.x - h, c.y - h, c.z - h),
        Point(c.x + h, c.y + h, c.z + h)
    );
}

bool AABB::isIntersect(const Triangle& tri) const {
    double triMinX = min({tri.v0.x, tri.v1.x, tri.v2.x});
    double triMaxX = max({tri.v0.x, tri.v1.x, tri.v2.x});
    double triMinY = min({tri.v0.y, tri.v1.y, tri.v2.y});
    double triMaxY = max({tri.v0.y, tri.v1.y, tri.v2.y});
    double triMinZ = min({tri.v0.z, tri.v1.z, tri.v2.z});
    double triMaxZ = max({tri.v0.z, tri.v1.z, tri.v2.z});
    return (minAABB.x <= triMaxX && maxAABB.x >= triMinX) &&
           (minAABB.y <= triMaxY && maxAABB.y >= triMinY) &&
           (minAABB.z <= triMaxZ && maxAABB.z >= triMinZ);
}