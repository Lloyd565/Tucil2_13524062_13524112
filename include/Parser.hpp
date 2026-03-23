#pragma once
#include <bits/stdc++.h>
#include "vertice.hpp"
#include "face.hpp"
using namespace std;

class Parser {
    public:
        vector<Vertice> vertice;
        vector<Face> face;
        void parse(const std::string& filepath) {
            ifstream file(filepath);
            if (!file.is_open()) throw runtime_error("TIdak bisa membuka file: " + filepath);
            
            string row;
            int nRow = 0;
            while (getline(file, row)){
                nRow++;
                if(row.empty()) continue;
                
                stringstream ss(row);
                string type;
                ss >> type;

                if (type == "v") {
                    double x, y, z;
                    if (!(ss >> x >> y >> z)) continue;
                    vertice.push_back(x);
                    vertice.push_back(y);
                    vertice.push_back(z);
                }
                else if (type == "f") {
                    int i, j, k;
                    if (!(ss >> i >> j >> k)) continue;
                    face.push_back(i);
                    face.push_back(j);
                    face.push_back(k);
                }
            }

            if (vertice.empty() || face.empty()) throw runtime_error("File tidak punya vertex atau faces sama sekali: " + filepath);
        }
};