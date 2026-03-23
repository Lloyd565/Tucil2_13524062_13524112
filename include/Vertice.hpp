#pragma once
#include <bits/stdc++.h>

class Vertice {
    public:
        double x, y, z;
        Vertice(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        Vertice operator+(const Vertice& other) const {
            return Vertice(x + other.x, y + other.y, z + other.z);
        }
        Vertice operator-(const Vertice& other) const {
            return Vertice(x - other.x, y - other.y, z - other.z);
        }
        Vertice operator*(double scalar) const {
            return Vertice(x * scalar, y * scalar, z * scalar);
        }
        Vertice operator/(double scalar) const {
            return Vertice(x / scalar, y / scalar, z / scalar);
        }

        Vertice cross(const Vertice& o) const {
        return {y*o.z - z*o.y,
                z*o.x - x*o.z,
                x*o.y - y*o.x};
        }
        double dot(const Vertice& o) const { return x*o.x + y*o.y + z*o.z; }
};