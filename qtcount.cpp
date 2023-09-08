#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */

    vector<RGBAPixel> leaves;
    getLeaves(node, leaves);
    for (RGBAPixel pixel : leaves) {
        if (colorDist(pixel, node->avg) >= tol) {
            return false;
        }
    }
    return true;
}


void qtcount::getLeaves(Node* node, vector<RGBAPixel>& leaves) const {
    if (!node) {
        return;
    }

    if (!node->NW && !node->NE && !node->SE && !node->SW) {
        leaves.push_back(node->avg);
    }

    getLeaves(node->NW, leaves);
    getLeaves(node->NE, leaves);
    getLeaves(node->SE, leaves);
    getLeaves(node->SW, leaves);

}

long qtcount::colorDist(RGBAPixel px1, RGBAPixel px2) const {
    return pow(px1.r - px2.r, 2) + pow(px1.g - px2.g, 2) + pow(px1.b - px2.b, 2);
}