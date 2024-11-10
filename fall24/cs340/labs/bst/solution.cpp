#include "treenode.h"
#include <queue>
#include <iostream>

bool isSameTree(TreeNode* p, TreeNode* q);
bool isSymmetricTree(TreeNode* p, TreeNode* q);
bool isOneTreePartOfAnother(TreeNode* p, TreeNode* q);
bool isSameHeap(TreeNode* p, TreeNode* q);
bool ofSameWidth(TreeNode* p, TreeNode* q);

auto max_width(TreeNode * root) -> int;
void postorder(TreeNode * p, TreeNode * q, TreeNode * match);
auto level_count(TreeNode * p) -> size_t;
auto is_maxheap(TreeNode * p) -> bool;


bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) {
        return true;
    }
    else if (p == nullptr && q == nullptr) {
        return false;
    }
    else if (p != nullptr && q == nullptr) {
        return false;
    }

    if (p != nullptr && q != nullptr) { 
        if (p->value != q->value)
            return false; 
        if (isSameTree(p->left, q->left) && isSameTree(p->right, q->right)) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}

bool isOneTreePartOfAnother(TreeNode* p, TreeNode* q) {
    if (p==nullptr && q == nullptr) {
        return false;
    }
    if (isSameTree(p,q)) {
        return true;
    }
    TreeNode * match = nullptr;
    postorder(p,q,match);
    if (match == nullptr)
        return false;
    if (isSameTree(p,match))
        return true;


    return false;

}

bool isSymmetricTree(TreeNode* p, TreeNode* q){
    if (p == nullptr && q == nullptr) {
        return true;
    }
    else if (p == nullptr && q == nullptr) {
        return false;
    }
    else if (p != nullptr && q == nullptr) {
        return false;
    }

    if (p != nullptr && q != nullptr) { 
        if (p->value != q->value)
            return false; 
        if (isSameTree(p->left, q->right) && isSameTree(p->right, q->left)) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;

    return false;
}


    // std::vector<int> p_widths = get_widths(p);
    // std::vector<int> q_widths = get_widths(q);
    //
    // int max_width_p = *std::max_element(p_widths.begin(), p_widths.end());
    // int max_width_q = *std::max_element(q_widths.begin(), q_widths.end());
    //
    // return (max_width_q == max_width_p);
    //
auto ofSameWidth(TreeNode* p, TreeNode*q) -> bool {
    return max_width(p) == max_width(q);
}
auto max_width(TreeNode * root) -> int {
    
    std::queue<TreeNode *> q;
    TreeNode * pp = nullptr;
    if (root) { q.push(root); q.push(nullptr) ;}

    int max_width = 0, current_width = 0;
    while (!q.empty()) {
        pp = q.front(); q.pop();

        if (pp == nullptr) {
            if (!q.empty()) q.push(nullptr);
            if (current_width > max_width)
                max_width = current_width;
            current_width = 0;
        } else
            ++current_width;

        if (pp != nullptr) {
            if (pp->left) q.push(pp->left);
            if (pp->right) q.push(pp->right);
        }
    }
    return max_width;
}

bool isSameHeap(TreeNode* p, TreeNode* q) {
    return isSameTree(p, q) && (is_maxheap(p) && is_maxheap(q));
}
void postorder(TreeNode * p, TreeNode * q, TreeNode * match) {
    if (q == nullptr) return;
    if (q != nullptr) {
        if (q == p) 
            match = q;
    }
    postorder(p, q->left, match);
    postorder(p, q->right, match);
}
auto is_maxheap(TreeNode * p) -> bool {
    if (p == nullptr) 
        return true;
    if (!p->left && !p->right) 
        return true;

    else {
        if (p->left)
            if (p->value < p->left->value) return false;
        if (p->right)
            if (p->value < p->right->value) return false;
    }

    return is_maxheap(p->left) && is_maxheap(p->right);
}

// int main() {
//     TreeNode * root1 = new TreeNode(30);
//     root1->left = new TreeNode(15);
//     root1->right = new TreeNode(20);
//
//     TreeNode * root2 = new TreeNode(9);
//     root2->left = new TreeNode(5);
//     root2->left->left = new TreeNode(5);
//     root2->right = new TreeNode(8);
//     root2->right->right = new TreeNode(8);
//     root2->right->left = new TreeNode(8);
//
//     std::cout << std::boolalpha << is_maxheap(root1);
// }
