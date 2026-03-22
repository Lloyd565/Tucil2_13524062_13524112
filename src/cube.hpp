#pragma once
#include "vertices.hpp"

class cube {
    public:
        vertices center;
        double half_size;
        cube(vertices center = {}) : center(center) {}
};