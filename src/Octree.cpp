#include "Octree.hpp"

Octree::Octree(const AABB& BB, bool isMaxDepth, bool isVoxel){
        this->BB = BB;
        for (int i = 0; i < 8; i++){
            children[i] = nullptr;
        }
        this->isMaxDepth = isMaxDepth;
        this->isVoxel = isVoxel;
}

Octree::~Octree() {
    for (int i = 0; i < 8; i++) {
        if(children[i] != nullptr){delete children[i];}
    }
}

vector<AABB> Octree::divideBB() const {
   vector<AABB> childBB(8);
   Point minP = BB.minAABB;
   Point maxP = BB.maxAABB;
   Point center = BB.center();

   childBB[0] = AABB(Point(minP.x, minP.y, minP.z), Point(center.x, center.y, center.z));
   childBB[1] = AABB(Point(center.x, minP.y, minP.z), Point(maxP.x, center.y, center.z));
   childBB[2] = AABB(Point(minP.x, center.y, minP.z), Point(center.x, maxP.y, center.z));
   childBB[3] = AABB(Point(center.x, center.y, minP.z), Point(maxP.x, maxP.y, center.z));
   childBB[4] = AABB(Point(minP.x, minP.y, center.z), Point(center.x, center.y, maxP.z));
   childBB[5] = AABB(Point(center.x, minP.y, center.z), Point(maxP.x, center.y, maxP.z));
   childBB[6] = AABB(Point(minP.x, center.y, center.z), Point(center.x, maxP.y, maxP.z));
   childBB[7] = AABB(Point(center.x, center.y, center.z), Point(maxP.x, maxP.y, maxP.z));

   return childBB;
}