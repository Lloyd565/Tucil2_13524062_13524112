#pragma once
#include <bits/stdc++.h>
using namespace std;

#define EMPTY_LEAF = nullptr;

template <typename T>
class Octree {
    public: 
        Octree<T>* children[8];
        Octree(T parent);
        T getParent();
        T getChild(int index);
    private:
        T parent_;
};