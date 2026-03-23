#pragma once
#include "Vertice.hpp"
#include "AABB.hpp"
#include "Triangle.hpp"
#include "Cube.hpp"
#include "TriangleMesh.hpp"
using namespace std;

class Utils {
    public:
        static AABB computeAABB(const Triangle& triangle) {
            Vertice min(
                min({triangle.v0.x, triangle.v1.x, triangle.v2.x}),
                min({triangle.v0.y, triangle.v1.y, triangle.v2.y}),
                min({triangle.v0.z, triangle.v1.z, triangle.v2.z})
            );
            Vertice max(
                max({triangle.v0.x, triangle.v1.x, triangle.v2.x}),
                max({triangle.v0.y, triangle.v1.y, triangle.v2.y}),
                max({triangle.v0.z, triangle.v1.z, triangle.v2.z})
            );
            return AABB(min, max);
        }
        // static AABB computeMeshAABB
};