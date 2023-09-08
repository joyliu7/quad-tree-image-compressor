/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    /* Your code here! */
     stats s(imIn);
     edge = min(imIn.width(), imIn.height());
     edge = log2(edge);
     edge = pow(2, edge);
     int dimIn = log2(edge);
    
     root = buildTree(s, make_pair(0, 0), dimIn);
}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    /* Your code here! */

    RGBAPixel avg = s.getAvg(ul, dim);
    double var = s.getVar(ul, dim);
    
    Node* subRoot = new Node(ul, dim, avg, var);

    if (dim == 0) {
        return subRoot;
    }

    int sideLength = pow(2, dim);
    pair<int, int> ul_NE = make_pair(ul.first + sideLength/2, ul.second);
    pair<int, int> ul_SW = make_pair(ul.first, ul.second + sideLength/2);
    pair<int, int> ul_SE = make_pair(ul.first + sideLength/2, ul.second + sideLength/2);

    subRoot->NW = buildTree(s, ul, dim-1);
    subRoot->NE = buildTree(s, ul_NE, dim-1);
    subRoot->SE = buildTree(s, ul_SE, dim-1);
    subRoot->SW = buildTree(s, ul_SW, dim-1);
    
    return subRoot;
}

PNG quadtree::render() const {
    /* Your code here! */
    PNG canvas(edge, edge);
    renderHelper(root, canvas);
    return canvas;
}

void quadtree::renderHelper(Node* curr, PNG& canvas) const {
    if (curr == nullptr) {
        return;
    }
    
    if (!curr->NW && !curr->NE && !curr->SW && !curr->SE) {
        int sideLength = pow(2, curr->dim);
        for (int i = curr->upLeft.first; i < curr->upLeft.first + sideLength; i++) {
            for (int j = curr->upLeft.second; j < curr->upLeft.second + sideLength; j++) {
                *canvas.getPixel(i, j) = curr->avg;

            }
        }

    }

    renderHelper(curr->NW, canvas);
    renderHelper(curr->NE, canvas);
    renderHelper(curr->SE, canvas);
    renderHelper(curr->SW, canvas);

}

int quadtree::idealPrune(const int leaves) const {
    /* Your code here! */
    
    for (int i = 0; i < 100000; i++) {
        if (pruneSize(i) >= leaves) {
            return i;
        }
    }
    return -1;
}

int quadtree::pruneSize(const int tol) const {
    /* Your code here! */
    if (root == nullptr) {
        return 0;
    }
    return pruneSizeHelper(root, tol);

}

int quadtree::pruneSizeHelper(Node* subRoot, const int tol) const {
    if (!subRoot) {
        return 0;
    }

    int count = 0;
    if (prunable(subRoot, tol)) {
        count++;
        return count;
    }

    int count1 = pruneSizeHelper(subRoot->NW, tol);
    int count2 = pruneSizeHelper(subRoot->NE, tol);
    int count3 = pruneSizeHelper(subRoot->SE, tol);
    int count4 = pruneSizeHelper(subRoot->SW, tol);

    return count1 + count2 + count3 + count4;
}

void quadtree::prune(const int tol) {
    /* Your code here! */
    pruneHelper(root, tol);

}

void quadtree::pruneHelper(Node* subRoot, const int tol) {
    if (subRoot == nullptr) {
        return;
    }

    if (prunable(subRoot, tol)) {
        subRoot->NW = nullptr;
        subRoot->NE = nullptr;
        subRoot->SE = nullptr;
        subRoot->SW = nullptr;

        return;
    }

    pruneHelper(subRoot->NW, tol);
    pruneHelper(subRoot->NE, tol);
    pruneHelper(subRoot->SE, tol);
    pruneHelper(subRoot->SW, tol);
}

void quadtree::clear() {
    /* your code here */
    if (root != nullptr) {
        clearHelper(root);
        root = nullptr;
    }
}

void quadtree::clearHelper(Node* subRoot) {

    if (subRoot != nullptr) {
        clearHelper(subRoot->NW);
        clearHelper(subRoot->NE);
        clearHelper(subRoot->SE);
        clearHelper(subRoot->SW);
        delete subRoot;
    }
}

void quadtree::copy(const quadtree& orig) {
    /* your code here */
    //clear();
    edge = orig.edge;
    root = copyHelper(orig.root);
}

quadtree::Node* quadtree::copyHelper(Node* subRoot) {
    if (subRoot == nullptr) {
        return nullptr;
    }

    Node* copied = new Node(subRoot->upLeft, subRoot->dim, subRoot->avg, subRoot->var);
    copied->NW = subRoot->NW;
    copied->NE = subRoot->NE;
    copied->SE = subRoot->SE;
    copied->SW = subRoot->SW;

    copied->NW = copyHelper(copied->NW);
    copied->NE = copyHelper(copied->NE);
    copied->SE = copyHelper(copied->SE);
    copied->SW = copyHelper(copied->SW);

    return copied;
}