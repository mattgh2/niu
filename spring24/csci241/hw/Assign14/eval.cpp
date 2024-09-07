//***************************************************************************
//
//  eval.cpp
//  CSCI 241 Assignment 14
//
//  Created by Matt Warner 
//
//***************************************************************************
#include "eval.h"
/**
 * evaluates a postfix expression and returns the calculated result
 *
 * @param a reference to a constant string holding the postfix expression
 *
 * @return and integer result of the evaluation
 */
int evaluate(const std::string& postfix) {
  
  // initilize a stack to holds tokens
  mystack eval_stack;
  int value = 0;
  std::string op;
  std::stringstream ss(postfix);

 // Loop that processes each token in the postfix string
  while (ss >> op) { 
      // Token is a integer
      if (isdigit(op[0])) {
        eval_stack.push(stoi(op));
      }
      // Token is a variable
      else if (isalpha(op[0])) {
        // Calculate value
        value = op[0] - 'a';
        // Push to stack
        eval_stack.push(value);
      }
      // Token is a ~
      else if (op[0] == '~') {
        char top_of_stack = eval_stack.top();
        eval_stack.pop();
        eval_stack.push(top_of_stack * -1);
      }
      else {
        // temp variables
        int result; // holds result of Calculation
        int right_operand;
        int left_operand;

        // Grab the right operand and remove from the stack
        right_operand = (int)eval_stack.top();
        eval_stack.pop();
        // grab the left operand and remove from the stack
        left_operand = (int)eval_stack.top();
        eval_stack.pop();

        if (op[0] == '*') { // perform multiplication and push the result to the stack
          result = left_operand * right_operand;
          eval_stack.push(result);
        }
        else if (op[0] == '/') { // perform division and push the result to the stack
          if (right_operand == 0) {
            std::cout << "*** Division by 0 ***" << std::endl;
          }
          else {
            result = left_operand / right_operand;
            eval_stack.push(result);
          }
        }
        else if (op[0] == '+') { // addition
          result = left_operand + right_operand;
          eval_stack.push(result);
        }
        else if (op[0] == '-') { // subtraction
          result = left_operand - right_operand;
          eval_stack.push(result);
        }
        else if (op[0] == '^') { // exponent
          result = 1;
          for (int i = 0; i < right_operand; i++) {
            result*= left_operand;
          }
          eval_stack.push(result);
        }
      }
  }

  return (!eval_stack.empty()) ? eval_stack.top() : 0;
}
