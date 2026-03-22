#pragma once

struct Point {
    double x,y,z;
    Point() : x(0), y(0), z(0) {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    Point operator=(const Point& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y, z - other.z);
    }
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y, z + other.z);
    }
    Point operator*(double scalar) const {
        return Point(x * scalar, y * scalar, z * scalar);
    }
};