#include "AABB.hpp"

bool AABB::intersectsTriangle(const Triangle& tri) const {
    double triMinX = std::min({tri.v0.x, tri.v1.x, tri.v2.x});
    double triMaxX = std::max({tri.v0.x, tri.v1.x, tri.v2.x});
    double triMinY = std::min({tri.v0.y, tri.v1.y, tri.v2.y});
    double triMaxY = std::max({tri.v0.y, tri.v1.y, tri.v2.y});
    double triMinZ = std::min({tri.v0.z, tri.v1.z, tri.v2.z});
    double triMaxZ = std::max({tri.v0.z, tri.v1.z, tri.v2.z});
    return (min.x <= triMaxX && max.x >= triMinX) &&
           (min.y <= triMaxY && max.y >= triMinY) &&
           (min.z <= triMaxZ && max.z >= triMinZ);
}