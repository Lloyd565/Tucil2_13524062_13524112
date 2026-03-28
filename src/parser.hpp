#pragma once
#include <bits/stdc++.h>
#include "Point.hpp"
using namespace std;

class Parser {
    public:
        vector<Point> vertices;
        vector<int> faces;
        ~Parser()=default;
        void parse(const string& filepath);
};