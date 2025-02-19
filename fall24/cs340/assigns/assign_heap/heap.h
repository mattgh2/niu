#ifndef NIU_CSCI340_HEAP_H
#define NIU_CSCI340_HEAP_H

#include <algorithm>
#include <stdexcept>
#include <queue>
#include <iostream>


// This file is the version distributed to students for implementation.

/**
 * Gets a nodes left child.
 */
inline constexpr size_t heap_left(size_t node) { 
    return (node << 1) + 1;
}
/**
 * Gets a nodes right child.
 */
inline constexpr size_t heap_right(size_t node) { 
    return (node << 1) + 2;
}
/**
 * Gets a nodes parent.
 */
inline constexpr size_t heap_parent(size_t node) {
    return (node > 0) ? (node - 1) >> 1 : 0; 
}

/**
 * pre order traversal procedure for a heap.
 */
template <typename ArrayLike, typename FN>
void heap_preorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node >= heapnodes) {
        return;
    }
    fn(heapdata[node]);
    heap_preorder(heapdata, heapnodes, heap_left(node), fn);
    heap_preorder(heapdata, heapnodes, heap_right(node), fn);
}

/**
 * in order traversal procedure for a heap.
 */
template <typename ArrayLike, typename FN>
void heap_inorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node >= heapnodes) {
        return;
    }
    heap_inorder(heapdata, heapnodes, heap_left(node), fn);
    fn(heapdata[node]);
    heap_inorder(heapdata, heapnodes, heap_right(node), fn);
}

/**
 * post order traversal procedure for a heap.
 */
template <typename ArrayLike, typename FN>
void heap_postorder(ArrayLike heapdata, size_t heapnodes, size_t node, FN fn) {
    if (node >= heapnodes) {
        return;
    }
    heap_postorder(heapdata, heapnodes, heap_left(node), fn);
    heap_postorder(heapdata, heapnodes, heap_right(node), fn);
    fn(heapdata[node]);
}
/**
 * level order traversal procedure for a heap.
 */
template <typename ArrayLike, typename FN>
void heap_levelorder(ArrayLike & heapdata, size_t heapnodes, FN fn) {

    // Check for empty heap.
    if (heapnodes == 0) return;

    std::queue<size_t> nodes;
    size_t current_node{};
    nodes.push(0);

    while (!nodes.empty()) {
        current_node = nodes.front();
        nodes.pop();
    
        fn(heapdata[current_node]);

        if (heap_left(current_node) < heapnodes) {
            nodes.push(heap_left(current_node));
        }
        if (heap_right(current_node) < heapnodes) {
            nodes.push(heap_right(current_node));
        }
    }
}

/**
 * Check if a given input range is a heap.
 * min tree uses less than, so compare(parent, child) should be true
 */
template <typename ArrayLike, typename COMPARISON>
bool is_heap(const ArrayLike & heapdata, size_t nodes, COMPARISON compare) { 

    // Iterate through all internal nodes.
    for (size_t i = 0; i <= heap_parent(nodes - 1); ++i) {

        // Get left and right children.
        size_t left = heap_left(i);
        size_t right = heap_right(i);
         
        bool has_left_child = (left < nodes);
        bool has_right_child = (right < nodes);

        // Check if  children exist before making comparisons with them.
        if (has_left_child) {
            if (compare(heapdata[i], heapdata[left]) == false) {
                return false;
            }
        }

        if (has_right_child) {
            if (compare(heapdata[i], heapdata[right]) == false) {
                return false;
            }
        }
    }
    return true;
}

/**
 * heap bubble up procedure.
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_up(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    if (start == 0) {
        return 0;
    }
    // Get the parent
    size_t parent = heap_parent(start);
    size_t swap_count{};

    size_t sibling{};
    // If the starting point is the left child, get the right child.
    if (heap_left(parent) == start) {
        sibling = start + 1; 
    }
    // If the starting point is the right child, get the left child.
    else if (heap_right(parent) == start) {
        sibling = start - 1;
    }
    size_t swap = parent;
    // Chekc if the child node should be swapped with its parent.
    if (compare(*(begin + start), *(begin+parent))) {
        swap = start;
    }

    // Chekc if the sibling node should be swapped with the result of compare(child, parent).
    else if (sibling < nodes && compare(*(begin+sibling), *(begin+swap))) {
        swap = sibling;
    }

    // If either of the swap checks returned true, swap the parent node with the node that belongs in parent.
    if (swap != parent) {
        std::iter_swap(begin+parent,begin+swap);
        ++swap_count;

        // Fix any violations above.
        swap_count+=heap_bubble_up(begin, nodes, parent, compare);

    }
    
    return swap_count;
}

/**
 * Heap bubble down procedure.
 */
template <typename RAIterator, typename COMPARE>
size_t heap_bubble_down(RAIterator begin, size_t nodes, size_t start, COMPARE compare) {
    RAIterator current = begin + start;
    RAIterator end = begin + nodes;

    // Left and right children.
    RAIterator left = begin + heap_left(start);
    RAIterator right = begin + heap_right(start);

    size_t swap_count{}; 

    // Node to swap with parent.
    size_t swap = start;

    // Check if left should be swapped with its parent.
    if (left < end && compare(*left, *current)) {
        swap = std::distance(begin, left);
    }

    // Check if left should be swapped with the result of compare(left, current).
    if (right < end && compare(*right, *(begin + swap))) {
        swap = std::distance(begin, right);
    }
    // If either of the swap checks returned true, swap the parent node with the node that belongs in parent.
    if (swap != start) {
        std::iter_swap(current, begin + swap);
        ++swap_count;
        // Fix any violations below.
         swap_count+=heap_bubble_down(begin, nodes, swap, compare);
    }
    return swap_count;
}
/**
 * Inserts a key into the heap of nodes.
 */
template <typename T, typename CONTAINER, typename COMPARISON>
void heap_insert(CONTAINER & heapdata, size_t &nodes, T key, COMPARISON compare) {

    // Inserts key and fixes any heap-property violations caused by insertion.
    heapdata[nodes] = key;
    heap_bubble_up(std::begin(heapdata), nodes + 1, nodes, compare);
    ++nodes;
}

/**
 * Removes the key stored at the root of the heap and returns its value.
 */
template <typename CONTAINER, typename COMPARISON> 
auto heap_extract(CONTAINER & heapdata, size_t &nodes, COMPARISON compare) {
    if (nodes == 0) 
        return 0;

    // Captures the root node and exchanges it with the final node in the tree.
    auto root = heapdata[0];
    heapdata[0] = heapdata[nodes - 1];

    // Fix the heap-property violation.
    heap_bubble_down(std::begin(heapdata), nodes - 1, 0, compare);

    // Remove the last node from the range.
    --nodes;

    return root;
}

/**
 * in-place top-down heapify procedure for a given range [begin, end).
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_up(RAIterator begin, RAIterator end, COMPARE compare) {
    size_t nodes = std::distance(begin,end);
    size_t swaps{};
    // Converts an array to heap in a top-down manner using heap_bubble_up on each subtree
    // starting at the first node that is not the root.
    for (size_t i = 1; i < nodes; ++i) {
        swaps += heap_bubble_up(begin, nodes, i, compare);
    }
    return swaps;
}
/**
 * in-place bottom-up heapify procedure for a given range [begin, end).
 */
template <typename RAIterator, typename COMPARE>
size_t heapify_in_place_down(RAIterator begin, RAIterator end, COMPARE compare) {
    size_t nodes = std::distance(begin,end);
    size_t swaps{};

    // Converts an array to heap in a bottom-up manner using heap_bubble_down on each subtree
    // starting at the last non-leaf node.
    for (int i = heap_parent(nodes - 1); i >= 0; --i) {
        swaps += heap_bubble_down(begin, nodes, i, compare);
    }
    return swaps;
}

/**
 * Sorts an input range using heapsort.
 */
template <typename RAIterator, typename COMPARE>
void heap_sort(RAIterator begin, RAIterator end, COMPARE compare) {

    // Heapify the range.
    heapify_in_place_down(begin, end, compare);

    // Each iteration swaps the last element with the first element, which puts it at its correct final position.
    // New root element might violate the heap property, so we adjust by bubbling down at the root. 
    for (auto last = end - 1; last > begin; --last ) {
        std::iter_swap(last, begin);
        heap_bubble_down(begin, std::distance(begin, last), 0, compare);
    }
}

#endif /* NIU_CSCI340_HEAP_H */

