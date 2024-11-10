/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 5
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* Provides functions for general binary tree functionality.
* Also provides some functionality for tilted binary trees.
* 
************************************************************************************/
#ifndef NIU_CSCI330_BINTREE_IMPL_H
#define NIU_CSCI330_BINTREE_IMPL_H

#include "bintree.decl.h"

#include <vector>
#include <queue>
#include <iostream>

template <typename node>
auto m_count_children(node * root) -> size_t;

template <typename node>
auto m_get_children(node * root, std::vector<node *> &children_nodes, size_t pos = 0) -> void;
/**
 * Performs a preorder walk on a binary tree.
 */
template <typename BINTREENODE, typename FN>
void preorder(BINTREENODE *root, FN fn) {
    if (root == nullptr) {
        return;
    }
    
    fn(root);
    preorder(root->left, fn);
    preorder(root->right, fn);
}

/**
 * Performs a inorder walk on a binary tree.
 */
template <typename BINTREENODE, typename FN>
void inorder(BINTREENODE *root, FN fn) {
    if (root == nullptr) {
        return;
    }
    
    inorder(root->left, fn);
    fn(root);
    inorder(root->right, fn);

}

/**
 * Performs a postorder walk on a binary tree.
 */
template <typename BINTREENODE, typename FN>
void postorder(BINTREENODE *root, FN fn) {
    if (root == nullptr) {
        return;
    }
    
    postorder(root->left, fn);
    postorder(root->right, fn);
    fn(root);
}

template <typename BINTREENODE, typename FN>
void levelorder(BINTREENODE *root, FN fn) {
    std::queue<BINTREENODE *> q;
    BINTREENODE * current_node = nullptr;

    q.push(root);
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

/**
 * Returns a vector of the direct children of the given node.
 */
template <typename BINTREENODE>
std::vector <BINTREENODE *> tilted_get_children(BINTREENODE * node) {

    // Get the number of children nodes to avoid reallocating the vector.
    size_t children_node_count = m_count_children(node->left);

    // Initialize vector of children nodes.
    std::vector<BINTREENODE *> children(children_node_count);
     
    m_get_children(node->left, children);
    
    return children;
}

/**
 * Finds a nodes parent.
 * This function requires that BINTREENODE have the parent member
 */
template <typename BINTREENODE>
BINTREENODE * tilted_find_parent(BINTREENODE *node) {
    
    BINTREENODE * current_parent = node->parent;
    
    if (current_parent == nullptr) {
        return nullptr;
    }
    if (node == current_parent->left) {
        return current_parent;
    }

    return tilted_find_parent(node->parent);
}

/**
 * Performs a levelorder walk on the tilted tree.
 */
template <typename BINTREENODE, typename FN>
void tilted_levelorder(BINTREENODE *root, FN fn) {

    std::queue<BINTREENODE * >  q;
    BINTREENODE * current_node = nullptr;

    q.push(root);
    while (!q.empty()) {

        // Get the node at the front of the queue.
        current_node = q.front();

        // Remove the current node from the queue after assignment.
        q.pop();

        // Perform operation on the current node.
        fn(current_node);

        // Add all children of current_node to the queue.
        for (const auto &child : tilted_get_children(current_node)) {
            q.push(child);
        }
    }
}

template <typename BINTREENODE>
void delete_tree(BINTREENODE * &node) {
    m_clear_tree_(node);

    // Reset root pointer.
    node = nullptr;
}
/**
 * Helper function for tilted_get_children.
 * Starts at the left child of the root node passed to tilted_get_children.
 * This avoids any recursive calls to the siblings of the root node.
 */
template <typename node>
auto m_get_children(node * root, std::vector<node *> &children_nodes, size_t pos) -> void {
    if (root == nullptr) return;

    children_nodes[pos] = root;

    m_get_children(root->right, children_nodes, pos + 1);
}

/**
 * Subroutine that finds the size of the tree rooted at U.
 */
template <typename node>
auto m_count_children(node * U) -> size_t {
    size_t node_count = 0;
    if (U == nullptr) return 0;

    return (++node_count += m_count_children(U->right));
}
/**
 * Clears the tree by deleting all nodes.
 */
template <typename BINTREENODE>
void m_clear_tree_(BINTREENODE * &node) {
   if (node == nullptr) return;

   m_clear_tree_(node->left);
   m_clear_tree_(node->right);

   delete node;
}
#endif
