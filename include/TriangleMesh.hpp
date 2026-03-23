#pragma once
#include <vector>
#include "Vertice.hpp"
#include "Face.hpp"
#include "Triangle.hpp"
using namespace std;

class TriangleMesh {
public:
    vector<Vertice> vertices;
    vector<Face> faces;
    vector<Triangle> triangles;

    TriangleMesh() = default;

    TriangleMesh(const std::vector<Vertice>& vertices,
                 const std::vector<Face>& faces)
        : vertices(vertices), faces(faces) {
        buildTriangles();
    }

    void buildTriangles() {
        triangles.clear();
        triangles.reserve(faces.size());

        for (const Face& face : faces) {
            triangles.emplace_back(
                vertices[face.i - 1],
                vertices[face.j - 1],
                vertices[face.k - 1]
            );
        }
    }
};