//***************************************************************************
//
//  mystack.cpp
//  CSCI 241 Assignment 11
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include "mystack.h"

/** Default constructor: Initilizes new mystack object to an empty stack.
 *
 */
mystack::mystack() {
 stackArray = nullptr;  
 stackCapacity = 0;
 stackSize = 0;
}
/**
 * Copy constructor: Initilizes a new mystack object to the same values 
 * for all of its data members as the mystack object that is passed into the function.
 *
 * @param x: a object of the mystack class.
 */
mystack::mystack(const mystack& x) {

   stackSize = x.stackSize;
   stackCapacity = x.stackCapacity;

  if (stackCapacity == 0)
    stackArray = nullptr;
  else
    stackArray = new char[ stackCapacity];
  
  // Loop that fills the new objects stackArray with the elements in the stackArray of object x.
  for (size_t i = 0; i < stackSize; i++) {
    stackArray[i] = x.stackArray[i];
  }
}
/**
 * class destructor: deletes the stack array.
 *
 */
mystack::~mystack() {
  delete[] stackArray;
}
/**
 * Overloaded assignment operator. Assigns one mystack object to another.
 *
 * @param x: a constant reference to a mystack object.
 *
 * @return a object of the mystack class
 *
 */
mystack& mystack::operator=(const mystack& x) {
  this-> stackCapacity = x.stackCapacity;
  this-> stackSize  = x.stackSize;

  if (stackCapacity == 0) {
    this-> stackArray = nullptr;
  }
  else {
    this-> stackArray = new char[stackCapacity];
  }
  for (size_t i = 0; i < stackSize; i++) {
    this-> stackArray[i] = x.stackArray[i];
  }
  return *this;
}
/**
 * Gets the capacity of the stack
 *
 * @return the stacks capacity
 */
size_t mystack::capacity() const {
  return stackCapacity;
}
/**
 * Gets the size of the stack
 *
 * @return the stacks size
 */
size_t mystack::size() const {
  return stackSize;
}
/**
 * Determines if a stack is empty
 *
 * @return true if the stack is empty, otherwise false.
 */
bool mystack::empty() const {
  return (stackSize == 0);
}
/**
 * sets the stack size back to 0
 *
 */
void mystack::clear() {
  stackSize = 0;
}
/**
 * Modifies an object's stack capacity without changing 
 * the stack size or the contents of the stack array
 *
 * @param n: the new stack capacity.
 *
 */
void mystack::reserve(size_t n) {

 if (n <= stackCapacity)
   return;

  stackCapacity = n;
  char *ptr = new char[stackCapacity];

  for (size_t i = 0; i < stackSize; i++) {
    ptr[i] = stackArray[i];
  }

  delete[] stackArray;
  stackArray = ptr;

}
/**
 * Gets the top of the stack.
 *
 * @return the top item of the stack.
 */
const char& mystack::top() const {
  return stackArray[stackSize - 1];
}
/**
 * Pushes a character to the top of the stack
 *
 * @param value: a character value
 *
 */
void mystack::push(char value) {

  // if the current stack capacity is zero, the capacity is increased by 1
  if (stackCapacity == 0)
    reserve(1);

  // If the stack is full, the capacity is doubled
  else if (stackSize == stackCapacity)  
    reserve(stackCapacity * 2);

  // adds value to the top of the stack
  stackArray[stackSize] = value;
  stackSize++; // increases stack size by 1
}
/**
 * pops the top item off of the stack by decreasing the stack size by 1
 *
 */
void mystack::pop() {
  stackSize--;
}
/**
 * Overloading the stream insertion operator to print the elements of the stack array.
 *
 * @param os: the stream insertion operator
 * @param obj: a reference to a constant object of the mystack class
 *
 * @return a reference to an ostream object
 *
 * @note: if the stack is empty, nothing will be printed.
 */
std::ostream& operator<<(std::ostream& os, const mystack& obj) {

  // prints the contents of the stack if stack is not empty.
  if (obj.stackSize > 0) {

    size_t i;
    for (i = 0; i < obj.stackSize - 1; i++) {
      os << obj.stackArray[i] << ", ";
    }
    os << obj.stackArray[i];
  }

  return os;
}
