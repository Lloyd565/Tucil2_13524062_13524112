#pragma once
#include "vertice.hpp"

class Triangle {
    public:
        Vertice v0, v1, v2;
        Triangle() : v0(), v1(), v2() {}
        Triangle(Vertice v0 = {}, Vertice v1 = {}, Vertice v2 = {}) : v0(v0), v1(v1), v2(v2) {}
};