//***************************************************************************
//
//  mylist.h
//  CSCI 241 Assignment 16
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#ifndef MYLIST_H
#define MYLIST_H

#include <ostream>

// Forward declaration of the mylist template class.
template <class T> class mylist;

// Forward declaration of the operator<< template function
template <class T> 
std::ostream& operator<<(std::ostream&, const mylist<T>&);


template <class T> struct node {

  T value; 
  node *prev;
  node *next;

  node(const T& value = T(), node<T> *prev = nullptr, node<T> *next = nullptr) {
    this->value = value;
    this-> prev = prev;
    this-> next = next;
  }
};

template <class T> class mylist { 

private:
  node<T> *front_node = nullptr;
  node<T> *back_node = nullptr;
  size_t list_size = 0;

public:

  friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&);

  // Defualt constructor
  mylist() = default;
  // Copy constructor
  mylist(const mylist<T>& x);
  // destructor
  ~mylist();
  
  // Methods
  mylist<T>& operator=(const mylist<T>&);
  void clear();
  size_t size() const;
  bool empty() const;
  const T& front() const;
  T& front();
  const T& back() const;
  T& back();
  void push_front(const T&);
  void push_back(const T&);
  void pop_front();
  void pop_back(); bool operator==(const mylist<T>&) const;
  void clone(const mylist<T>&);
  bool operator <(const mylist<T>&) const;

};

template <class T> 
/**
 * Destructor
 *
 */
mylist<T>::~mylist() {
  clear();
}

/**
 * copy constructor:
 *
 * @param a constant mylist object
 *
 */
template <class T> 
mylist<T>::mylist(const mylist<T>& x) {

  front_node = nullptr;
  back_node = nullptr;
  list_size = 0;
   
  clone(x);

}
/**
 * overloading the assignment operator 
 * to allow the assignment of an object of the mylist class to another
 *
 * @param a const mylist object of type T used as the right hand side of assignment
 *
 * @return a reference to a mylist object of type T (the object on the left hand side of assignment)
 */
template <class T> 
mylist<T>& mylist<T>::operator=(const mylist<T> &x) {
  if ((this == &x) == false) {
    clear();

    clone(x);
  }
  return *this;
}
/**
 * deletes all of the nodes in the linked list, 
 * setting the linked list back to an empty state.
 *
 */
template <class T>
void mylist<T>::clear() {
  while (!empty())
    pop_front();
}
/**
 * Gets the size of a linked list
 *
 * @return the list's size
 */
template <class T>
size_t mylist<T>::size() const {
  return this->list_size;
}
/**
 * determines if a linked list is empty
 *
 * @return true if list is empty, otherwise false
 */
template <class T>
bool mylist<T>::empty() const {
  return (list_size == 0);
}
/**
 * Grabs the value of the front node
 *
 * @return a reference to a const value of type T
 */
template <class T> 
const T& mylist<T>::front() const {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to front()");
  } else {
    return front_node->value;
  }
}
/**
 * Grabs the value of the front node
 *
 * @return a reference to a value of type T
 */
template <class T>
T& mylist<T>::front() {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to front()");
  } else {
    return front_node->value;
  }
}
/**
 * Grabs the value of the back node
 *
 * @return a reference to a const value of type T
 * 
 * note: const version of back()
 */ 
template <class T> 
const T& mylist<T>::back() const {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to back()");
  } else {
    return back_node->value;
  }
}
/**
 * Grabs the value of the back node
 *
 * @return a reference to a value of type T
 */
template <class T>
T& mylist<T>::back() {

  if (empty()) {
    throw std::underflow_error("underflow exception on call to back()");
  } else {
    return back_node->value;
  }
}
/**
 * pushes a new node to the front of the linked list
 *
 * @param a value for the new node
 *
 * note: Same exact logic used in push_back
 */
template <class T>
void mylist<T>::push_front(const T& value) {

  node<T> *new_node = new node<T>(value);

  if (!empty()) {
    new_node->next = front_node;
    front_node->prev = new_node;
    front_node = new_node;
  }
  else {
    front_node = new_node;
    back_node = new_node;
  }
  list_size++;
}
/**
 * pushs a new node to the back of the linked list.
 *
 * @param a value for the new node
 *
 */
template <class T>
void mylist<T>::push_back(const T& value) {

  node<T> *new_node = new node<T>(value); // allocate a new node

 // there is atleast one node
  if (!empty()) {

    // Points new node's prev pointer at current last node in the list
    new_node->prev = back_node;

    // Point current last node's next pointer at new last node in the list
    back_node->next = new_node;

    // Point back node at new last node in the list
    back_node = new_node;
  }
  else {
    front_node = new_node;
    back_node = new_node;
  }

  list_size++; 
}
/**
 * pops the front node from the linked list
 *
 * note: same logic as pop_back
 */
template <class T>
void mylist<T>::pop_front() {
  if (empty()) {
    throw std::underflow_error("underflow exception on call to pop_front()");
  }
  else {

    node<T> *del_node = front_node;
    if (list_size > 1) {

      front_node = del_node->next;

      front_node->prev = nullptr;

      delete del_node;
      list_size--;
    }
    else {
      front_node = del_node->next; 
      back_node = nullptr;
      delete del_node;
      list_size--;
    }
  }
}
/**
 * pops the back node from the linked list
 *
 */
template <class T>
void mylist<T>::pop_back() {

  if (empty()) {
    throw std::underflow_error("underflow exception on call to pop_back()");
  }
  else {
    // Save address of node to delete in a pointer
    node<T>* del_node = back_node;
    
    // List contains two or more nodes
    if (list_size > 1) {

      // Point back node at the new last node in the list
      back_node = del_node->prev;

      // Set the new last node's next pointer to nullptr
      back_node->next = nullptr;

      delete del_node;
      list_size--;
    }
    // List only contains one node 
    else {
      back_node = del_node->prev;   
      front_node = nullptr;
      delete del_node;
      list_size--;
    }
  }
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
  return true;
}
/**
 * overloads the less than operator to allow comparison of two mylist object.
 *
 * @param An object of the mylist class that is used as the right hand side of the comparison
 *
 * @return true if list1 (lhs) is less than list2 (rhs), otherwise the function returns false
 *
 * note: performs lexicographical comparison.
 */
template <class T>
bool mylist<T>::operator<(const mylist<T>& rhs) const {

  // declares two nodes used to traverse the lists and compare values
  node<T> *temp_node_one = this->front_node;
  node<T> *temp_node_two = rhs.front_node;

  // loops through node comparison until either list has reached the end
  while (temp_node_one != nullptr && temp_node_two != nullptr) {

    if (temp_node_one->value < temp_node_two->value) {
      return true;
    }
     
    else if (temp_node_one->value == temp_node_two->value) {

      // Moves to the next elements
      temp_node_one = temp_node_one->next;
      temp_node_two = temp_node_two->next;
    }

    else { // List1 (lhs) is not less than List2(rhs)
      return false;
    }
  }
  // Case for full equality, with list 1 having less elements
  if (this-> list_size < rhs.list_size)
    return true;

  return false;
}
/**
 * Overloading the stream insertion opeator to print the elements of a list
 *
 * @param the stream insertion operator and a mystack object
 *
 * @return a reference to an ostream object
 */
template <class T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj) {

  // traversal node starting at the front
  node<T> *ptr = obj.front_node; 

  // Loops through each node, 
  // printing their values until we hit a node that points to 0x0
  while (ptr != nullptr) {
  
    if (ptr->next != nullptr)
      os << ptr->value << " ";
    else
      os << ptr->value;

    ptr = ptr->next;
  }
  return os;
}
/**
 * helper function for deep copy, copys the nodes of one object to another
 *
 * @param a reference to a const mylist object
 *
 */
template <class T>
void mylist<T>::clone(const mylist<T> &obj) {

  // node used for traversing the linked list, starts at the back
  node<T> *ptr = obj.back_node; 
  
  // loops through each node, copies node to front
  while (ptr != nullptr) {
    push_front(ptr->value);
    ptr = ptr->prev;
  }
}

#endif
