#pragma once
#include "Vertice.hpp"

struct AABB {
    Vertice min;
    Vertice max;

    AABB() : min(), max() {}
    AABB(const Vertice& min, const Vertice& max) : min(min), max(max) {}
};