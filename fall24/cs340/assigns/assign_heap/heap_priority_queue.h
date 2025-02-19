
#ifndef NIU_CSCI340_HEAP_PQ_H
#define NIU_CSCI340_HEAP_PQ_H

// This file is the version distributed to students for implementation.

#include "heap_priority_queue.decl.h"
#include <queue>
/**
 * Constructor that takes a containers input range.
 * Copies the range into the heap, heapifying it.
 */ 
template <class T, class CONTAINER, class COMPARE>
template <class ITERATOR>
heap_priority_queue<T,CONTAINER,COMPARE>::heap_priority_queue(ITERATOR begin, ITERATOR end) {
    nodes = std::distance(begin, end);
    data.resize(nodes);

    std::copy(begin, end,data.begin());
    heapify_in_place_down(data.begin(), data.end(), compare);
}

/**
 * Gets a reference to the top of the heap.
 */
template <class T, class CONTAINER, class COMPARE>
T & heap_priority_queue<T,CONTAINER,COMPARE>::top() {
    return data.front();
}

/**
 * Checks if a heap is empty.
 */
template <class T, class CONTAINER, class COMPARE>
bool heap_priority_queue<T,CONTAINER,COMPARE>::empty() const {
    return nodes == 0;
}

/**
 * Gets the number of nodes currently in the heap.
 */
template <class T, class CONTAINER, class COMPARE>
size_t heap_priority_queue<T,CONTAINER,COMPARE>::size() const {
    return nodes;
}

/**
 * Inserts a key into the heap.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::push(const T & x) {
   data.resize(nodes + 1);
   heap_insert(data, nodes, x, compare);
}

/**
 * removes the value currently at the top of the heap.
 */
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::pop() {
    heap_extract(data, nodes, compare);
}

// This one is provided for you and does not need changes.
template <class T, class CONTAINER, class COMPARE>
void heap_priority_queue<T,CONTAINER,COMPARE>::dump_data(std::ostream &ost) const {
  ost << "[ ";
  for(size_t i = 0; i < nodes; ++i) {
    ost << data[i] << " "; }
  ost << "]"; }


#endif /* NIU_CSCI340_HEAP_PQ_H */
