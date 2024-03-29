#include "eval.h"
int evaluate(const std::string& postfix) {
  
  // initilize a stack to hold operands
  mystack eval_stack;
  int value = 0;
  std::string op;
  std::stringstream ss(postfix);

  while (ss >> op) { 
    for (const char& token : op) {
      // Token is a integer
      if (isalnum(token)) {
        eval_stack.push(token);
      }
      // Token is a variable
      else if (isalpha(token)) {
        // Calculate value
        value = token - 'a';
        // Push to stack
        eval_stack.push(value);
      }
      // Token is a ~
      else if (token == '~') {
        char top_of_stack = eval_stack.top();
        eval_stack.pop();
        eval_stack.push(~top_of_stack);
      }
      else {
        
      }
    }
  }


  return 1;
}
// Values: a = 0
//         b = 1
//         c = 2
