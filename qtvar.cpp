#include "qtvar.h"

bool qtvar::prunable(Node* node, const int tol) const {
    /* Your code here! */
    if (node == nullptr) {
        return true;
    }
    return node->var < tol;
}
