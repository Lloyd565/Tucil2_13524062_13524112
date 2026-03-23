#include "Octree.hpp"

template <typename T>
Octree<T>::Octree(T parent) {
    this->parent = parent;
    for (int i = 0; i < 8; i++) {
        children[i] = EMPTY_LEAF;
    }
}
template <typename T>
T Octree<T>::getParent() {
    return this->parent;
}

template <typename T>
T Octree<T>::getChild(int index) {
    if (index > 0 && index < 8) {
        return children[index];
    }
    return EMPTY_LEAF;
}