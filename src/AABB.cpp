#include "AABB.hpp"
#include <algorithm>

Point AABB::center() const {
    return Point(
        (minAABB.x + maxAABB.x)/2,
        (minAABB.y + maxAABB.y)/2,
        (minAABB.z + maxAABB.z)/2
    );
}

AABB AABB::makeUniCube() const {
    double dx = maxAABB.x - minAABB.x;
    double dy = maxAABB.y - minAABB.y;
    double dz = maxAABB.z - minAABB.z;
    double sref = std::max({dx, dy, dz});
    Point c = center();
    double h = sref/2;
    return AABB(
        Point(c.x - h, c.y - h, c.z - h),
        Point(c.x + h, c.y + h, c.z + h)
    );
}

AABB AABB::fromTriangle(const Triangle& tri) const {
    double x0 = std::min({tri.v0.x, tri.v1.x, tri.v2.x});
    double y0 = std::min({tri.v0.y, tri.v1.y, tri.v2.y});
    double z0 = std::min({tri.v0.z, tri.v1.z, tri.v2.z});
    double x1 = std::max({tri.v0.x, tri.v1.x, tri.v2.x});
    double y1 = std::max({tri.v0.y, tri.v1.y, tri.v2.y});
    double z1 = std::max({tri.v0.z, tri.v1.z, tri.v2.z});
    return AABB(Point(x0, y0, z0), Point(x1, y1, z1));
}

bool AABB::overlaps(const AABB& other) const {
    bool sepX = maxAABB.x < other.minAABB.x || other.maxAABB.x < minAABB.x;
    bool sepY = maxAABB.y < other.minAABB.y || other.maxAABB.y < minAABB.y;
    bool sepZ = maxAABB.z < other.minAABB.z || other.maxAABB.z < minAABB.z;
    return !sepX && !sepY && !sepZ;
}

bool AABB::isIntersect(const Triangle& tri) const {
    return overlaps(fromTriangle(tri));
}

bool AABB::isIntersectSAT(const Triangle& tri) const {
    Point c = center();
    Point halfSize(
        (maxAABB.x-minAABB.x)/2,
        (maxAABB.y-minAABB.y)/2,
        (maxAABB.z-minAABB.z)/2
    );
    Point v0 = tri.v0-c;
    Point v1 = tri.v1-c;
    Point v2 = tri.v2-c;
    Point e0 = v1-v0;
    Point e1 = v2-v1;
    Point e2 = v0-v2;

    auto satCrossX = [&](double ay, double az) -> bool {
        double p0 = ay * v0.y + az * v0.z;
        double p1 = ay * v1.y + az * v1.z;
        double p2 = ay * v2.y + az * v2.z;
        double r = halfSize.y * std::abs(ay) + halfSize.z * std::abs(az);
        return std::min(p0, std::min(p1, p2))<=r && std::max(p0, std::max(p1, p2))>=-r;
    };
    auto satCrossY = [&](double ax, double az) -> bool {
        double p0 = ax * v0.x + az * v0.z;
        double p1 = ax * v1.x + az * v1.z;
        double p2 = ax * v2.x + az * v2.z;
        double r = halfSize.x * std::abs(ax) + halfSize.z * std::abs(az);
        return std::min(p0, std::min(p1, p2))<=r && std::max(p0, std::max(p1, p2))>=-r;
    };
    auto satCrossZ = [&](double ax, double ay) -> bool {
        double p0 = ax * v0.x + ay * v0.y;
        double p1 = ax * v1.x + ay * v1.y;
        double p2 = ax * v2.x + ay * v2.y;
        double r = halfSize.x * std::abs(ax) + halfSize.y * std::abs(ay);
        return std::min(p0, std::min(p1, p2))<=r && std::max(p0, std::max(p1, p2))>=-r;
    };
    if (!satCrossX(-e0.z, e0.y)) return false;
    if (!satCrossX(-e1.z, e1.y)) return false;
    if (!satCrossX(-e2.z, e2.y)) return false;
    if (!satCrossY(e0.z, -e0.x)) return false;
    if (!satCrossY(e1.z, -e1.x)) return false;
    if (!satCrossY(e2.z, -e2.x)) return false;
    if (!satCrossZ(-e0.y, e0.x)) return false;
    if (!satCrossZ(-e1.y, e1.x)) return false;
    if (!satCrossZ(-e2.y, e2.x)) return false;
    //3 sumbu utamanya
    if (std::max({v0.x, v1.x, v2.x})<-halfSize.x || std::min({v0.x, v1.x, v2.x})>halfSize.x) return false;
    if (std::max({v0.y, v1.y, v2.y})<-halfSize.y || std::min({v0.y, v1.y, v2.y})>halfSize.y) return false;
    if (std::max({v0.z, v1.z, v2.z})<-halfSize.z || std::min({v0.z, v1.z, v2.z})>halfSize.z) return false;
    //normal dari triangle
    double nx = e0.y*e1.z-e0.z*e1.y;
    double ny = e0.z*e1.x-e0.x*e1.z;
    double nz = e0.x*e1.y-e0.y*e1.x;
    double d = nx * v0.x + ny * v0.y + nz * v0.z;
    double r = halfSize.x * std::abs(nx) + halfSize.y * std::abs(ny) + halfSize.z * std::abs(nz);
    if (d>r || d<-r) return false;
    return true;
}