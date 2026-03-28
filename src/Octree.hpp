#pragma once
#include "AABB.hpp"
#include <bits/stdc++.h>
using namespace std;

class Octree {
    public:
        AABB BB;
        Octree* children[8];
        bool isMaxDepth;
        bool isVoxel;
        
        Octree(const AABB& bb, bool isMaxDepth=false, bool isVoxel=false);
        ~Octree();
        vector<AABB> divideBB() const;
};