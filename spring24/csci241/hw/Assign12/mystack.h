//***************************************************************************
//
//  mystack.h
//  CSCI 241 Assignment 11
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#ifndef MYSTACK_H
#define MYSTACK_H

#include <cstddef>
#include <ostream>

class mystack {

private:
  // Data members
  char *stackArray;
  size_t stackCapacity;
  size_t stackSize;

public:

  // contructors
  mystack();
  mystack(const mystack& x);

  // destructor
  ~mystack();

  // Operation overloading
  mystack& operator=(const mystack& x);
  
  // friend declaration for stream insertion operator overloading
  friend std::ostream& operator<<(std::ostream& os, const mystack& obj);

  // Class methods
  size_t capacity() const;
  size_t size() const;
  bool empty() const;
  void clear();
  void reserve(size_t n);
  const char& top() const;
  void push(char value);
  void pop();
};

std::ostream& operator<<(std::ostream& os, const mystack& obj);

#endif
