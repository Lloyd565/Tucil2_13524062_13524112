#pragma once
#include <bits/stdc++.h>
using namespace std;

class Parser {
    public:
        vector<int> vertices;
        vector<int> faces;
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
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(z);
                }
                else if (type == "f") {
                    int i, j, k;
                    if (!(ss >> i >> j >> k)) continue;
                    faces.push_back(i);
                    faces.push_back(j);
                    faces.push_back(k);
                }
            }

            if (vertices.empty() || faces.empty()) throw runtime_error("File tidak punya vertex atau faces sama sekali: " + filepath);
        }
};