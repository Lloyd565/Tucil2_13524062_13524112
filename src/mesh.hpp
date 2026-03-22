#pragma once
#include "vertices.hpp"
#include "faces.hpp"
#include "triangles.hpp"

class mesh {
    public:
        std::vector<vertices> vertices;
        std::vector<faces> faces;
        std::vector<triangles> triangles;
};