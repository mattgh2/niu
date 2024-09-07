//***************************************************************************
//
//  bstree.h
//  CSCI 241 Assignment 17
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#ifndef BSTREE_H
#define BSTREE_H

#include <queue>
#include <stack>
#include <iostream>

// Defining node structure
template <class K, class V> 
struct node {

  K key;
  V value;
  node<K,V> *left;
  node<K,V> *right;

  node(const K& key = K(), const V& value = V(), node<K,V> *left = nullptr, node<K,V> *right = nullptr) {
    this->key = key;
    this->value = value;
    this-> left = left;
    this->right = right;
  }
};

template<class K, class V> class bstree {
private: 
  
  /*
   Data members
    : Root node
    : Tree size
  */
  node<K,V> *root = nullptr;
  size_t t_size = 0; 
  
public:  
  
  bstree() = default;
  ~bstree();
  bstree(const bstree<K,V> &);
  bstree<K,V>& operator=(const bstree<K,V> &);

  void clear();
  size_t size() const;
  size_t height() const;
  bool empty() const;
  const K& min() const;
  const K& max() const;
  bool insert(const K& key, const V& value);
  bool remove(const K& key);
  const node<K,V>* find(const K& key) const;

  // Traversal member functions
  void preorder() const;
  void inorder() const;
  void postorder() const;
  void level_order() const;

  // Helper functions
  void destroy(node<K,V> *p);
  node<K,V>* clone(node<K,V> *p);
};
/**
 * Class destructor
 *
 */
template <class K, class V>
bstree<K, V>::~bstree() {
  clear();
}
/**
 * Copy constructor: Copies over a BS tree
 *
 * @param: A reference to a BS tree
 *
 */
template <class K, class V>
bstree<K, V>::bstree(const bstree<K,V>& x) {

  if (!x.empty()) {
    // Copy the other bstree object's size
    t_size = x.t_size;

    // Copy the nodes of the other bstree object
    this->root = clone(x.root);
  }
}
/**
 * Overloading the assignment operator 
 * to allow the assignment of an object of the bstree class to another
 *
 * @param a reference to a bstree object of type <K,V> used as the right hand side of assignment
 *
 * @return a reference to a bstree object of type <K,V> (the object on the left hand side of assignment)
 */
template <class K, class V>
bstree<K, V>& bstree<K, V>::operator=(const bstree<K,V>& x) {
 if (this != &x) {
   // Make the left bstree empty
   clear();

   // Copy the other bstree object's size
   t_size = x.t_size;

   // Copy the nodes of the other bstree object
   root = clone(x.root);
 }
 return *this;
}
/**
 * Sets the tree back to its empty state.
 *
 * Note: Uses helper function destroy() to properly delete all tree nodes
 */
template <class K, class V>
void bstree<K, V>::clear() {
  destroy(root);
  root = nullptr;
  t_size = 0;
}
/**
 * Gets the number of nodes (size) from a tree.
 *
 * @return the size of the tree
 */ 
template <class K, class V>
size_t bstree<K,V>::size() const {
  return t_size;
}
/**
 * Finds the height of the tree.
 *
 *
 * @return the height of the tree
 *
 * Note: Uses level order traversal (BFS) to traverse the tree level by level, 
 *       incrementing the height after each level is cleared. 
 *       a nullptr is inserted into the queue before the start of a new level,
 *       so we know when to increment the height.
 */
template <class K, class V>
size_t bstree<K,V>::height() const {

  size_t height = 0;

  if (empty()) {
    height = 0;
    return height;
  }
  // Only root
  if (t_size == 1) {
    height = 1;
    return height;
  }
  else {
    node<K,V> *p;
    std::queue<node<K,V>*> q; // create our queue

    q.push(root); // Start at the root node 
    q.push(nullptr); // Also push nullptr, so we can keep track of the start of new levels
    
    // Loops untill there are no more nodes to traverse,
    while (!q.empty()) {

      // get the node at the front of the queue and pop the node.
      p = q.front(); 
      q.pop();

      // If its null, increment height
      if (!p) {
        height++;
      }

      // If current pointer is a node, add its children
      if (p) { 
        if (p->left != nullptr) {
          q.push(p->left);
        }
        if (p->right != nullptr) {
          q.push(p->right);
        }
      }
      // current pointer is null, meaning the queue has all the nodes on the level, 
      // so nullptr gets pushed to the queue.
      else if (!q.empty()){
          q.push(nullptr);
      }
    }
  }
  return height;
}
/** 
 * Determines if the tree is empty
 *
 * @return true if empty, otherwise false
 */
template <class K, class V>
bool bstree<K, V>::empty() const {
  return (t_size == 0);
}
/**
 * Finds the minimum key in the tree.
 *
 * @return A node with the minimum key 
 */
template <class K, class V>
const K& bstree<K,V>::min() const {

  node<K,V> *p; // node pointer, used to traverse the BS tree
  
  p = root; // Start at root node

  // minimum key will be the left-most node.
  // loops untill our node pointer reaches that node.
  while (p->left != nullptr) {
    p = p->left;
  }

  return p->key;
}
/**
 * Finds the maximum key in the tree
 *
 * @return A node with the maximum key
 */
template <class K, class V>
const K& bstree<K, V>::max() const {
  node<K,V> *p; // node pointer, used to traverse the BS tree.

  p = root; // Start at root
  
  // maximum key will be the right-most node.
  // Loops untill our node pointer reaches that node
  while (p->right != nullptr) {
    p = p->right;
  }

  return p->key;
}
/**
 * Attempts to insert a key and value into the binary search tree. 
 *
 * @param A key and a value
 *
 * @return A signal of the insertions success or failure.
 *
 * Note: If the key already exists in the tree, the function returns false.
 *       Otherwise, a new tree node containing the key and value gets added into the tree
 */
template <class K, class V>
bool bstree<K, V>::insert(const K& key, const V& value) {

  node<K,V> *p; // Pointer to a tree node
  node<K,V> *parent; // Pointer to the parent node of p

  p = this->root; // Start p at root node
  parent = nullptr;

  // Search the tree for a null link or a duplicate key
  while (p != nullptr && key != p->key) {
    parent = p;
    if (key < p->key) { // go left
      p = p->left;
    } else { // go right
      p = p->right; 
    }
  }
  // Key already exists in tree
  if (p != nullptr) {
    return false;
  }
  // Otherwise, create a tree node and insert it as a new leaf nod.
  node<K,V> *new_node = new node<K,V>(key, value);

  // empty tree
  if (parent == nullptr) {
    root = new_node;
  }
  // new node belongs as left child of parent
  else if (new_node->key < parent->key) {
    parent->left = new_node;
  }
  // new node belongs as right child parent
  else {
    parent->right = new_node;
  }
  // Increment size and and signal success
  t_size++;
  return true;
}
/**
 * Attempts to remove the specified key from the BS tree.
 *
 * @param The key to search for in the tree
 *
 * @return a signal of the removals success or failure 
 *         If the key is not found, returns false 
 *         Otherwise, the function returns true 
 */
template <class K, class V>
bool bstree<K, V>::remove(const K& key) {

  node<K,V> *p; // Pointer to the node to delete from the tree
  node<K,V> *parent; // Pointer to the parent node of the node to delete from the tree
  node<K,V> *replace; // Pointer to node that will replace the deleted node
  node<K,V> *replace_parent; // Pointer to parent of node that will replace the deleted node
  
  // Start at the root of the tree and search for the key to delete 
  p = this->root;
  parent = nullptr;
  while (p != nullptr && key != p->key) {
    parent = p;
    if (key < p->key) {
      p = p->left;
    } else {
      p = p->right;
    }
  }
  // If the node to delete was not found, signal failure.
  if (p == nullptr) {
    return false;
  }
  // p has no children, or p has no left child but has a right child.
  // replace p with right child
  if (p->left == nullptr) {
    replace = p->right;
  }
  // p has a left child but no right child. Replace p with its left child
  else if (p->right == nullptr) {
    replace = p->left;
  }

  // p has two children. Replace p with its inorder predecessor.
  else {

    // Go left
    replace_parent = p;
    replace = p->left;

    // Traverse farthest right
    while (replace->right != nullptr) {
      replace_parent = replace; 
      replace = replace->right;
    }

    // If we were able to go to the right
    if (replace_parent != p) {

      // Make the replacement node's left child the right child of its parent.
      replace_parent->right = replace->left;
      // Make the left child of p the replacement's left child
      replace->left = p->left;
    }
    // Make the right child of p the replacement's right child
    replace->right = p->right;
  }
  // connect replacement node to the parent node of p
  // or the root if p has no parent
  if (parent == nullptr) {
    root = replace;
  } 
  else {
    if (p->key < parent->key) {
      parent->left = replace;
    }
    else {
      parent->right = replace;
    }
  }
  // Delete the node pointed to by p
  delete p;

  t_size--;
  return true;

}
/**
 * Attempts to find the specific key in the BS tree.
 *
 * @param The key to search for in the tree
 *
 * @return the address of the node that contains the key if the key was found 
 *         Otherwise, nullptr is returned
 */
template <class K, class V>
const node<K, V>* bstree<K, V>::find(const K& key) const {

  node<K,V> *p; // pointer to a tree node

  p = root; // Start at the root node

  // Loops until the key is found or the end of the tree is hit.
  while (p != nullptr && key != p->key) {

    if (key < p->key) {
      p = p->left; // Go left
    }
    else {
      p = p->right; // Go right
    }
  }
  return p;
}
/**
 * Preforms a preorder traversal of the tree from left to right. 
 * As each node is visited, its key and value is printed.
 *
 */
template <class K, class V>
void bstree<K, V>::preorder() const {

  node<K,V> *p = root; // pointer to a tree node
  std::stack<node<K,V>*> s; // a stack of pointers to tree nodes
  
  while (p != nullptr || !s.empty()) {
    
    // Traverses all the way left
    while (p != nullptr) {

      // Print key, value for current node
      std::cout << p->key << ": " << p->value << std::endl;

      // Place a pointer to the node on the stack before
      // traversing the node's left subtree
      s.push(p);
      p = p->left;
    }
    // Backtrack one level
    p = s.top();
    s.pop();

    // traverse the node's right subtree
    p = p->right;
  }
}
/**
 * Preforms a inorder traversal of the tree from left to right.
 * As each node is visited, its key and value is printed
 *
 */
template <class K, class V>
void bstree<K, V>::inorder() const {

  node<K,V> *p = root; // pointer to a tree node, starts at root
  std::stack<node<K,V>*> s; // a stack of pointers to tree nodes

  while (p != nullptr || !s.empty()) {
    while (p != nullptr) {

      s.push(p);
      p = p->left;
    }

    p = s.top();
    s.pop();

    std::cout << p->key << ": " << p->value << std::endl;

    p = p->right;
  }
}
/**
 * Preforms a post order traversal of the tree
 * As each node is visited, its key and value is printed
 *
 */
template <class K, class V>
void bstree<K, V>::postorder() const {
  node<K,V> *p;  // pointer to a tree node
  node<K,V> *last_visited; // pointer to the last tree node visited
  std::stack<node<K,V>*> s; // a stack of pointers to tree nodes
   
  last_visited = nullptr; 
  p = root; // Start at the root node

  while (p != nullptr && last_visited != root) {

    // Go all the way to the left
    while (p != nullptr && p != last_visited) {

      // Place a pointer to the node on the stack before
      // traversing the node's left subtree
      s.push(p);
      p = p->left;
    }
    // backtrack one level
    p = s.top();
    s.pop();
     
    // If this node has no right child
    // or we've already traversed its right subtree
    if (p->right == nullptr || p->right == last_visited) {
      // Print the nodes key,value
      std::cout << p->key << ": " << p->value << std::endl;
      // Mark the node as last visited
      last_visited = p;
    }
    else { // traverse the node's right subtree
      s.push(p);
      p = p->right;
    }
  }
}
/**
 * Preforms a level order traversal of the tree from left to right.
 * As each node is visited, its key and value is printed
 *
 */
template <class K, class V>
void bstree<K, V>::level_order() const {

  node<K,V> *p; // pointer to a tree node
  std::queue<node<K,V>*> q;  // A queue of pointers to tree nodes

  // Return if tree is empty 
  if (empty()) {
    return;
  }

  // Start by adding root node to queue
  q.push(root);
  
  while (!q.empty()) {
    // Remove front item in the queue and visit it.
    p = q.front();
    q.pop();
    std::cout << p->key << ": " << p->value << std::endl;

    // Insert left child of p into queue
    if (p->left != nullptr) {
      q.push(p->left);
    }
    // Insert right child of p into queue
    if (p->right != nullptr) {
      q.push(p->right);
    }
  }
}
/**
 * Recursively deletes all nodes in a tree
 *
 * @param a pointer to a tree node, used as the starting point for deletion
 *
 */
template <class K, class V>
void bstree<K,V>::destroy(node<K,V> *p) {

  if (p != nullptr) {

    // Recursively destroy the left and right subrees of the node pointed to by p
    destroy(p->left);
    destroy(p->right);

    // Delete the node pointed to by p
    delete p;
  }
}
/**
 * helper function for deep copy, copys the nodes of one object to another
 *
 * @param a reference to a const bstree object
 *
 */
template<class K, class V>
node<K,V>* bstree<K,V>::clone(node<K,V> *p) {
  if (p != nullptr) {

    // Make a copy of the node
    node<K,V> *new_node = new node<K,V>(p->key, p->value);
    new_node->left = clone(p->left);
    new_node->right = clone(p->right);

    return new_node;
  }
  else {
    return nullptr;
  }
}

#endif
