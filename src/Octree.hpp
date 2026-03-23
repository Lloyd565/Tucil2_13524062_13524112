#pragma once
#include <bits/stdc++.h>
using namespace std;

#define EMPTY_LEAF = nullptr;

template <typename T>
class Octree {
    public: 
        Octree(T parent) {
            this->parent = parent;
            for (int i = 0; i < 8; i++) {
                children[i] = EMPTY_LEAF;
            }
        }
        T getParent() {
            return parent;
        }
        T getChild(int index) {
            if (index > 0 && index < 8) {
                return children[index];
            }
            return EMPTY_LEAF;
        }
    private:
        Octree<T>* children[8];
        T parent;
};