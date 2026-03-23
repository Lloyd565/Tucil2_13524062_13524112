#pragma once
#include "Vertice.hpp"

class Cube {
    public:
        Vertice center;
        double half;

        Cube() : center(), half(0.0) {}
        Cube(Vertice center = {}, double half = 0.0) : center(center), half(half) {}
};