#pragma once
#include "parser.hpp"
#include <bits/stdc++.h>
using namespace std;

class TriangleMesh {
    public:
        vector<int> mesh;
        vector<int> vertices;
        TriangleMesh(const std::string& filepath) {
            Parser parser;
            parser.parse(filepath);
            vertices = parser.vertices;
            faces = parser.faces;
            for (int i = 0; i < faces.size() / 3; i++) {
                mesh.push_back(vertices[faces[i*3] - 1]);
                mesh.push_back(vertices[faces[i*3 + 1] - 1]);
                mesh.push_back(vertices[faces[i*3 + 2] - 1]);
            }
        }
    private:
        vector<int> faces;
};
