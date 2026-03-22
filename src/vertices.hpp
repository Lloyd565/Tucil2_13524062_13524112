#pragma once
#include <bits/stdc++.h>

class vertices {
    public:
        double x, y, z;
        vertices(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        vertices operator+(const vertices& other) const {
            return vertices(x + other.x, y + other.y, z + other.z);
        }
        vertices operator-(const vertices& other) const {
            return vertices(x - other.x, y - other.y, z - other.z);
        }
        vertices operator*(double scalar) const {
            return vertices(x * scalar, y * scalar, z * scalar);
        }
        vertices operator/(double scalar) const {
            return vertices(x / scalar, y / scalar, z / scalar);
        }

        vertices cross(const vertices& o) const {
        return {y*o.z - z*o.y,
                z*o.x - x*o.z,
                x*o.y - y*o.x};
        }
        double dot(const vertices& o) const { return x*o.x + y*o.y + z*o.z; }
};