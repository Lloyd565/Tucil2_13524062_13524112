#pragma once
#include "vertices.hpp"

class triangles {
    public:
        vertices v1, v2, v3;
        triangles(vertices v1 = {}, vertices v2 = {}, vertices v3 = {}) : v1(v1), v2(v2), v3(v3) {}
};