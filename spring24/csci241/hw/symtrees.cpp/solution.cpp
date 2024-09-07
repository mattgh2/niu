#include <queue>
#include "node.h"
#include <iostream>

bool symmetric(node *t1, node* t2) { 
  if (!t1 && !t2) { return true;}
  if (!t1 || !t2) {return false;}

  std::queue<node*> q1;
  std::queue<node*> q2;

  q1.push(t1->left); q1.push(t1->right); q2.push(t2->right); q2.push(t2->left);

  while (!q1.empty() && !q2.empty()) {

    // levels are same
    if (q1.size() == q2.size()) {

      size_t q_len = q1.size();
      for (size_t i = 0; i < q_len; i++) {
        node *j = q1.front();
        node *k = q2.front();

        if ((!j && k) || (j && !k)) {
          return false;
        }
        else {
          if (j != nullptr) {
            q1.push(j->left); q1.push(j->right);
          }
          if (k != nullptr) {
            q2.push(k->right); q2.push(k->left);
          }
          q1.pop(); q2.pop();
        }
      }
    } else {
      return false;
    }
  }
  return (q1.empty() && q2.empty()) ? true : false;
}

