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

  node(T value, node *prev, node *next) {
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
  mylist<T>& operator=(const mylist<T>&);
  void clear();
  size_t size() const;
  bool empty() const;
  T& front() const;
  const T&
};

#endif
