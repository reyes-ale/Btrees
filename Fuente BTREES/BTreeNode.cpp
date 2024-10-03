#include "BTreeNode.h"
#include <iostream>

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];

    num_claves = 0; 
}

\
BTreeNode::~BTreeNode() {
    delete[] keys;
    delete[] C;
}