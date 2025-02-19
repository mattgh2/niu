
/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 6
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* Provides functions for general binary tree functionality.
* 
************************************************************************************/
#ifndef LEHUTA_BINTREE_H_IMPL
#define LEHUTA_BINTREE_H_IMPL


#include "bintree.decl.h"
#include <queue>

template <typename BINTREENODE>
void m_clear_tree_(BINTREENODE * &node);

// height of tree, defined as the number of edges in the longest path
// from the root to a leaf. If you're off the tree, this should return -1.
//
template <typename NODE>
int height(NODE * node) {
    if (node == nullptr) {
        return -1;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);
   
    return std::max(left_height, right_height) + 1;
}
/**
 * Counts the number of nodes in the tree.
 */
template <typename NODE>
int count(NODE * root) {
    int count = 0;
    // Perform a preorder walk on the tree, counting each node visited.
    preorder(root, [&count](const auto &node) {++count;});

    return count;

}
/**
 * Perform a preorder walk on the tree.
 */
template <typename NODE, typename FN>
void preorder(NODE *root, FN fn) {
    if (root == nullptr) return;

    fn(root); 
    preorder(root->left, fn);
    preorder(root->right, fn);
}

/**
 * Perform a inorder walk on the tree.
 */
template <typename NODE, typename FN>
void inorder(NODE *root, FN fn) {
    if (root == nullptr) return;

    inorder(root->left, fn);
    fn(root); // Visit node.
    inorder(root->right, fn);
}
/**
 * Perform a postorder walk on the tree.
 */
template <typename NODE, typename FN>
void postorder(NODE *root, FN fn) {
    if (root == nullptr) return;
    postorder(root->left, fn);
    postorder(root->right, fn);
    fn(root); // Visit node.
}

/**
 * Performs a levelorder walk on the tree.
 */
template <typename NODE, typename FN>
void levelorder(NODE *root, FN fn) {
    std::queue<NODE *> q;
    NODE * current_node = nullptr;

    if (root) q.push(root);
    while (!q.empty()) {

        // Get the node at the front of the queue.
        current_node = q.front();

        // Remove the current node from the queue after assignment.
        q.pop();

        // Perform operation on current_node.
        fn(current_node); 

        // Push children to the queue.
        if (current_node->left) q.push(current_node->left);
        if (current_node->right) q.push(current_node->right);
    }
}

template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
    m_clear_tree_(node);

    // Reset root pointer.
    node = nullptr;
}

template <typename BINTREENODE>
void m_clear_tree_(BINTREENODE * &node) {
   if (node == nullptr) return;

   m_clear_tree_(node->left);
   m_clear_tree_(node->right);

   delete node;
}

#endif
