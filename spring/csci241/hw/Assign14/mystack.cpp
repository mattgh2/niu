//***************************************************************************
//
//  mystack.cpp
//  CSCI 241 Assignment 13
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include "mystack.h"
/**
 * Copy constructor : initializes a new mystack object, copys data from ecisting object x to new object
 * 
 *
 * @param x: a reference to a constant mystack object.
 *
 */
mystack::mystack(const mystack &x) {
  
  // checks for empty stack
  if (x.stackSize < 1) {
    this-> head = nullptr;
  }
  // stack is not empty, copies over data.
  else {
    this-> stackSize = x.stackSize;
    // copy the other stack's linked list
    clone(x); 
  }
}
/**
 * Class destructor: sets the stack back to empty state
 *
 */
mystack::~mystack() {
  clear();
}
/**
 * overloaded " = " operator. Assigns one mystack object to another.
 *
 * @param x: a reference to a constant mystack object.
 *
 * @return a reference to a mystack object. 
 */
mystack& mystack::operator=(const mystack &x) {
  // checks for empty stack
  if (x.stackSize < 1) {
    this-> head = nullptr;
  }
  else { // stack not empty
    this-> stackSize = x.stackSize;
    // copy the other stack's linked list
    clone(x);
  }
  return *this;
}
/**
 * Gets the size of the stack
 *
 * @return The stack size
 */
size_t mystack::size() const {
  return this-> stackSize;
}
/**
 * gets the state of the stack (empty or not).
 *
 * @return true if the stack is empty, otherwise false
 */
bool mystack::empty() const {
  return (stackSize == 0);
}
/**
 * Sets the stack back to the empty state.
 *
 */
void mystack::clear() {
  // repeatedly calling pop() until the stack is empty.
  while (!empty()) {
    pop();
  }
}
/**
 * Gets the top item of the stack
 *
 * @return the value on the top of the stack
 */
const int& mystack::top() const {
 return head-> value;
}
/**
 * Inserts a new intem at the top of the stack
 *
 * @param the value that will be placed at the top of the stack
 *
 */
void mystack::push(int value) {

  // Allocate a new stack node
  node* new_node = new node(value, head);

  // set the top of stack to new_node
  head = new_node;

  // increase size
  stackSize++;
}
/**
 * Removes the top item off the stack
 *
 */
void mystack::pop() {
  node* delete_node = head;
  head = head->next;

  delete[] delete_node;
  stackSize--;
}
/**
 * overloading the " << " operator: prints the data in the stack.
 * 
 * @param os: the stream insertion operator
 * @param obj: a reference to a constant object of the mystack class
 *
 * @return a reference to an ostream object
 *
 * @note: if the stack is empty, nothing will be printed.
 */
std::ostream& operator<<(std::ostream& os, const mystack& obj) {
  if (!obj.empty()) {

    mystack::node* ptr = nullptr; // Allocating new node
    ptr = obj.head;

    // loops through each node
    while (ptr != nullptr) { // ends when it points to a null address 
      
      if (ptr-> next == nullptr) { // prints last node (without the comma)
        os << ptr-> value;
      }

      else { // prints every other node (with comma)
        os << ptr-> value << ", "; // prints the nodes data
      }

      ptr=ptr->next; // moves to next node
    }
  }
  return os;  
}
/**
 * Copies the linked list from the stack x to this object
 *
 * @param a reference to a constant mystack object
 *
 */
void mystack::clone(const mystack& obj) {

  node* last = nullptr;
  node* ptr = obj.head;
  
  // Loops that copies over nodes
  while (ptr != nullptr) {
    node *new_node = new node(ptr->value); // Allocate new node

    if (last == nullptr) {
      this->head = new_node;
    }
    else {
      last->next = new_node;
    }
    last = new_node;
    ptr = ptr->next;
  }
}

