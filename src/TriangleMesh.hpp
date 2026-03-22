#pragma once
#include "parser.hpp"
#include <bits/stdc++.h>
using namespace std;

class TriangleMesh {
    public:
        vector<Point> mesh;
        vector<Point> vertices;
        TriangleMesh(const std::string& filepath) {
        }
    private:
        vector<int> faces;
};
