// NODEP * insert = new NODEP(value); // Input item 
// NODEP * trailing_parent = nullptr; // parent to x
// NODEP * x = root; // pointer to trace a path down the tree
//
// // Moves the two pointers, trailing_parent and x down the tree,
// // finding the position where the input item should insert.
// while (x != nullptr) {
//     trailing_parent = x; 
//     if (x->data > value) {
//         x = x->left;
//     } else {
//         x = x->right;
//     }
// }
//
// // point the input items parent node to the parent found above.
// insert->parent = trailing_parent;
//
// // Tree is empty.
// if (trailing_parent == nullptr)
//     root = insert;
//
// // Insert node as left child if parent is greater.
// else if (trailing_parent->data > value)
//     trailing_parent->left = insert;
// // Insert node as right child if parent is less.
// else
//     trailing_parent->right = insert;
//
// return insert;
//
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
#ifndef NIU_CSCI340_BST_H_IMPL
#define NIU_CSCI340_BST_H_IMPL

#include "bst.decl.h"
#include <iostream>
#include <algorithm>
#include <vector>

template <typename NODE, typename Op>
auto in_order_walk(NODE * root, Op f) -> void;
template <typename NODEP>
auto transplant(NODEP * &root, NODEP * del, NODEP *v) -> void;

/**
 * Finds a node in the tree.
 */
template <typename NODE, typename T>
NODE * bst_find(NODE *root, const T & value) {

    while (root != nullptr) {
        // Value found in tree.
        if (root->data == value) {
            return root;
        }
        // Value must be in left subtree.
        if (root->data > value) {
            root = root->left;
        }
        // Value must be in right subtree.
        else {
            root = root->right;
        }
    }
    // Value DNE in tree.
    return nullptr;
}

/**
 * Inserts a node into the tree.
 */
template <typename NODEP, typename T>
NODEP * bst_insert(NODEP * &root, const T & value) {

    if (root == nullptr) {
        root = new NODEP(value);
        return root;
    }
    if (root->data > value) {
        root->left = bst_insert(root->left, value);
        root->left->parent = root;
    } 
    else if (root->data < value) {
        root->right = bst_insert(root->right, value);
        root->right->parent = root;
    }
    return root;
}
/**
 * Searches for a value in the tree, if the value exists, 
 * It is deleted from the tree.
 * 
 * @param root The root of the binary serach tree.
 * @param value The value to remove from the tree.
 *
 * @return The position on the tree closest to where the  change occured.
 */
template <typename NODEP, typename T>
NODEP * bst_remove_value(NODEP * &root, const T & value) {
    NODEP * delete_node = bst_find(root, value);

    // Value does not exist in the tree.
    if (delete_node == nullptr) return nullptr;

    // One or zero children with left child missing.
    if (delete_node->left == nullptr) {
        transplant(root, delete_node, delete_node->right);
    }

    // Node only has a left child.
    else if (delete_node->right == nullptr) {
        transplant(root, delete_node, delete_node->left);
    }
    // Node has two children.
    else {
        // Find the nodes successor.
        NODEP * del_successor = successor(delete_node);

        // Replace the successor as a child of its parent by the successor's right child 
        // and turn the deletion nodes right child into the sucessor's right child.
        if (del_successor->parent != delete_node) {
            transplant(root, del_successor, del_successor->right);
            del_successor->right = delete_node->right;
            del_successor->right->parent = del_successor;
        }
        // Replace the deletion node as a child of its parent by its successor 
        // and replace the successors left child by the deletion nodes left child.
        transplant(root, delete_node, del_successor);
        del_successor->left = delete_node->left;
        del_successor->left->parent = del_successor;
    }

    NODEP * parent = delete_node->parent;
    delete delete_node;
    return (parent == nullptr) ? root : parent;
}

/**
 * Determines if a given tree is a binary search tree.
 *
 * @param root The root node of the tree.
 *
 * @return true if the tree is a BST.
 */
template <typename NODE>
bool is_bst(NODE *root) {
    if (root == nullptr) return true;

    // Vector to hold data from tree.
    std::vector<decltype(root->data)> tree_nodes;
    
    // Perform an inorder walk, adding each nodes data to the vector.
    in_order_walk(root, [&] (NODE * node) { tree_nodes.push_back(node->data);});

    // An inorder tree walk will yield a sorted array if the tree is a valid Bst.
    return (std::ranges::is_sorted(tree_nodes));

}
/**
 * Finds the minumum value in the tree.
 *
 * @param root The root of the tree.
 *
 * @return the trees min node.
 */
template <typename NODE>
inline NODE * bst_minimum(NODE * root) {
    if (root == nullptr) {
        return nullptr;
    }
    // Traverse all the way left.
    while (root->left != nullptr) { 
        root = root->left; 
    }

    return root;
}
/**
 * Finds the maximum value in the tree.
 *
 * @param root The root of the tree.
 *
 * @return The trees node containing the max value.
 */
template <typename NODE>
inline NODE * bst_maximum(NODE * root) {
    if (root == nullptr) {
        return nullptr;
    }
    while (root->right != nullptr) { 
        root = root->right; 
    }
    return root;
}

/**
 * Find the immediate successor of a node in the tree.
 *
 * @param node A node in the tree.
 *
 * @return The nodes successor.
 */
template <typename NODEP>
NODEP * successor(NODEP * node) {
    if (node->right != nullptr) {
        return bst_minimum(node->right);
    }
    NODEP * parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

/**
 * Performs an inorder walk on the tree.
 *
 * @param root The root of the tree.
 * @param f A function object.
 */
template <typename NODE, typename Op>
auto in_order_walk(NODE * root, Op f) -> void {
    if (root == nullptr) return;
    in_order_walk(root->left, f);
    f(root);
    in_order_walk(root->right, f);
}
/**
 * sub routine for deleting nodes from the tree.
 */
template <typename NODEP>
auto transplant(NODEP * &root, NODEP * del, NODEP *v) -> void {
    // del is the root node. 
    if (del->parent == nullptr) {
        root = v;
    }
    // Update parents left child or right child to the node rooted at v.
    else if (del == del->parent->left) {
        del->parent->left = v;
    }
    else {
        del->parent->right = v;
    }

    // Update v's parent pointer to the correct location.
    if (v != nullptr) {
        v->parent = del->parent;
    }

}
#endif
