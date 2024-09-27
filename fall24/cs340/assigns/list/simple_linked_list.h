/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 3
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* Provides implementations for the member functions of a simple_linked_list.
************************************************************************************/
#ifndef NIUCSCI340_LIST_H
#define NIUCSCI340_LIST_H

#include "simple_linked_list.decl.h"

#include <iostream>

/**
 * Range copy constructor for a simply_linked_list.
 * Performs a copy on all nodes in range and inserts them into the list.
 *
 */
template <typename T>
template <typename ITERATOR> // constructor copying the contents of another container
simple_linked_list <T>::simple_linked_list(ITERATOR beg, ITERATOR end) {

    // Initialize list to a working state.
    head = tail = nullptr;
    n_elements = 0;

    // Sets the head and tail node to the start of the range.
    linked_node<T>* new_node = new linked_node<T>(*beg);
    head = tail = new_node;
    ++n_elements;

    // Iterate through range.
    while (++beg != end) {

        // Allocate a new node.
        new_node = new linked_node<T>(*beg);

        // Point current tails next pointer to new node.
        tail->next = new_node;

        // Set tail to new node.
        tail = new_node;

        // Update size.
        ++n_elements;
    }
}

/**
 * Checks for an empty state.
 *
 * @return True if the container is empty. Otherwise false.
 */
template <typename T>
bool simple_linked_list<T>::empty() const {
  return !(n_elements);
}

/**
 * Returns an iterator pointing to the first node.
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::begin() {

  return simple_linked_iterator(head);
}

/**
 * Returns an iterator pointing to one past the end of the linked list.
 */
template <typename T>
simple_linked_iterator <T> simple_linked_list<T>::end() {
    return simple_linked_iterator(tail->next);
}

/**
 * Gets the value from the head node.
 *
 *
 * @return The value contained in the head (front) node.
 */
template <typename T>
T & simple_linked_list<T>::front() {
    return head->data;
}

/**
 * Gets the value from the tail node.
 *
 * @return The value contained in the tail (back) node.
 */ 
template <typename T>
T & simple_linked_list<T>::back() {
    return tail->data;
}

/**
 * Pops the last node from the back of the list.
 * Calling this function on an empty container results in a no-op.
 *
 */
template <typename T>
void simple_linked_list<T>::pop_back() {

    // No op.
    if (empty()) { return; }

    // Handles case for single node.
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    
    else {

        linked_node<T>* new_tail = head;

       // Traverse the linked list untill we reach
       // the node that will become our new tail.
        while (new_tail->next != tail) {
            new_tail = new_tail->next;
        }

        // Free our tail from memory.
        delete tail;

        // Point tail to our new tail. 
        tail = new_tail;

        // Point tails next pointer to 0.
        tail->next = nullptr;
    }

    // Update size.
    --n_elements;

}

/**
 * Inserts a new node into the back of the container.
 *
 * @param x Value used to construct the new node.
 *
 */
template <typename T>
void simple_linked_list<T>::push_back(const T & x) {

    // Allocate a new node with value x.
    linked_node<T>* new_node = new linked_node<T>(x, nullptr);

    // This is the first node in the list. 
    // head and hail should both be pointing to it.
    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    // Point the current tail nodes next pointer to the new node.
    // Point our tail node to our new node.
    else {
        tail->next = new_node;
        tail = new_node;
    }

    // Update size.
    ++n_elements;
}

/**
 * Destructor.
 * Erases all elements from the container.
 *
 */
template <typename T>
simple_linked_list<T>::~simple_linked_list() {
    clear();
}
/**
 * Returns the size of the list.
 */
template <class T>
size_t simple_linked_list<T>::size() const {
    return n_elements;
}
/**
 * Erases all elements from the container.
 *
 */
template <typename T>
void simple_linked_list<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

// IMPLEMENTATIONS FOR ITERATOR

/**
 * Overloaded equality operator.
 * Checks if two iterators point to the same node.
 *
 *
 * @return True if both iterators are pointing to the same node.
 */
template <typename T>
bool simple_linked_iterator<T>::operator == (const simple_linked_iterator <T> & other) const {
  return (pos == other.pos);
}

/**
 * Preincrement operator.
 *
 * @return A reference to an iterator after it is incremented to point to the next node.
 */
template <typename T>
simple_linked_iterator <T> & simple_linked_iterator <T>::operator ++ () { // preincrement
    // Move to the next node.
    pos = pos->next;

    // Return current entity.
    return *this;


}
/**
 * Postincrement operator.
 *
 * @return An iterator that captures its state before incrementing.
 */  
template <typename T>
simple_linked_iterator <T> simple_linked_iterator<T>::operator ++ (int) { // postincrement
  
  // Capture state of iterator before increment.
  simple_linked_iterator before_increment = *this;

  // Call prefix operator.
  ++(*this);

  // return state before increment.
  return before_increment;

}
/**
 * Deferences an iterator
 *
 * @return the value of the node pointed to by the iterator.
 */ 
template <typename T>
T & simple_linked_iterator<T>::operator * () { // dereference operator
    return pos->data;
}

#endif

