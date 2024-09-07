//***************************************************************************
//
//  file-name
//  CSCI 241 Assignment assignment-number
//
//  Created by name(s) and z-ID(s)
//
//***************************************************************************
#include "mylist.h"
#include <stdexcept>
template <class T> 

mylist<T>::~mylist() {
  clear();
}

template <class T> 
mylist<T>::mylist(const mylist<T>& x) {

  front_node = nullptr;
  back_node = nullptr;
  list_size = 0;
   
  clone(x);

}

template <class T> 
mylist<T>& mylist<T>::operator=(const mylist<T> &x) {
  if (!(this == &x)) {
    clear();

    clone(x);
  }
  return *this;
}

template <class T>
void mylist<T>::clear() {
  while (front_node != nullptr)  {
    pop_front();
    
  }
}
template <class T>
size_t mylist<T>::size() const {
  return list_size; 
}

template <class T>
bool mylist<T>::empty() const {
  return (list_size == 0);
}

template <class T> 
const T& mylist<T>::front() const {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to front()");
  } else {
    return front_node->value;
  }
}
template <class T>
T& mylist<T>::front() {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to front()");
  } else {
    return front_node->value;
  }
}

template <class T> 
const T& mylist<T>::back() const {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to back()");
  } else {
    return back_node->value;
  }
}

template <class T>
T& mylist<T>::back() {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to back()");
  } else {
    return back_node->value;
  }
}

template <class T>
void mylist<T>::push_front(const T& value) {

  node<T> *new_node = new node<T>(value, nullptr, nullptr);

  if (!empty()) {
    new_node->next = front_node;
    front_node->prev = new_node;
    front_node = new_node;
  }
  else {
    front_node = new_node;
    back_node = new_node;
  }
}

template <class T>
void mylist<T>::push_back(const T& value) {

  node<T> *new_node = new node<T>(value, nullptr, nullptr); // allocate a new node

  // If there is atleast one node
  if (!empty()) {
    new_node->prev = back_node;
    back_node->next = new_node;
    back_node = new_node;
  }
  else {
    front_node = new_node;
    back_node = new_node;
  }
  
}

template <class T>
void mylist<T>::pop_front() {
 node<T> del_node = front_node; 

 front_node = del_node.next;

 front_node->prev = nullptr;

 delete del_node;
}
template <class T>
void mylist<T>::pop_back() {

  // Save address of node to delete in a pointer
  node<T>* del_node = back_node;

  // Point back node at the new last node in the list
  back_node = del_node->prev;
  // Set the new last node's next pointer to nullptr
  back_node->next = nullptr;

  delete del_node;
}

template <class T>
bool mylist<T>::operator==(const mylist<T>& rhs) const {

  // base test for size equality
  if (this->list_size == rhs.list_size) {

    // using 2 pointers to traverse both lists and test all nodes for equality
    node<T> *traversal_node_lhs = this->front_node;
    node<T> *traversal_node_rhs = rhs.front_node;

    // Tests each node for equality
    while (traversal_node_lhs != nullptr) {
      if (traversal_node_lhs->value != traversal_node_rhs->value) {
        return false;
      }
      traversal_node_lhs = traversal_node_lhs->next;
      traversal_node_rhs = traversal_node_rhs->next;
    }
  }
  // differs in size, cannot be equal
  else {
    return false;
  }

}
template <class T>
bool mylist<T>::operator<(const mylist<T>& rhs) const {

  // declares two nodes used to traverse the lists and compare values
  node<T> *temp_node_one;
  node<T> *temp_node_two;

  // Gets the smaller of the two lists
  while (temp_node_one != nullptr && temp_node_two != nullptr) {

    if (temp_node_one->value < temp_node_two->value) {
      return true;
    }
    
    else if (temp_node_one->value == temp_node_two->value) {
      // Moves to the next node
      temp_node_one = temp_node_two->prev;
      temp_node_two = temp_node_two->prev;
    }

    else { // List1 (lhs) is not less than List2(rhs)
      return false;
    }
  }
  // Case for full equality, but list 1 has less elements
  if (this-> list_size < rhs.list_size)
    return true;

  return false;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {
  node<T> *ptr = obj.front_node;
  while (ptr != nullptr) {
    if (ptr->next != nullptr)
      os << ptr << " ";
    else
      os << ptr;
    ptr = ptr->next;
  }
  return os;
}

template <class T>
void clone(const mylist<T> &obj) {
  node<T> *ptr = obj.front_node; 

  while (ptr != nullptr) {
    push_front(ptr->value);
    ptr = ptr->next;
  }
}






