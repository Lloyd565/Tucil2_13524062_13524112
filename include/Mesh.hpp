#pragma once
#include "vertice.hpp"
#include "face.hpp"
#include "triangle.hpp"

class mesh {
    public:
        std::vector<Vertice> vertice;
        std::vector<Face> face;
        std::vector<triangle> triangle;
};