#ifndef MYSTACK_H 
#define MYSTACK_H

#include <cstdlib>
#include <ostream>


class mystack {

private:

  struct node {

    node* next;
    int value;

    node(int value, node* next = nullptr) {
      this-> value = value;
      this-> next = next;
    }

  };

  node* head = nullptr;
  size_t stackSize = 0;

  

public:
  mystack() = default;
  mystack(const mystack& x);
  ~mystack();

  friend std::ostream& operator<<(std::ostream& os, const mystack& obj);
  mystack& operator=(const mystack &x);
  size_t size() const;
  bool empty() const;
  void clear();
  const int& top() const;
  void push(int);
  void pop();
  void clone(const mystack&);


};

std::ostream& operator<<(std::ostream& os, const mystack& obj);
  
#endif
