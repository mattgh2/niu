//***************************************************************************
//
//  inpost.cpp
//  CSCI 241 Assignment 12
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include "inpost.h"
#include "mystack.h"
/**
 * converts an infix expression to postfix notation.
 *
 * @param infix: an infix expression
 *
 * @return the infix expression converted to its postfix representation
 */
std::string convert(const std::string& infix) 
{
  std::string postfix;
  mystack opstack; // a stack to hold operators during conversion

  // Loops through the infix expression, extracting and processing one token at a time.
  for (int i = 0; i < (int)infix.length(); i++) {

    // variable [a-z]
    if (std::islower(infix[i])) 
    {
      postfix+= infix[i];
      postfix+= ' ';
    }

    // Numeric literal
    else if (isdigit(infix[i])) {

      // Appends all of its digits to the postfix string
      for (; isdigit(infix[i]); i++) {
          postfix+= infix[i];
      }
      postfix += ' ';
      i--; // goes back to the correct index
    }

    // ignores whitespace
    else if (isspace(infix[i]))
      continue;
  
    // Pushes left parenthesis to the stack
    else if (infix[i] == '(')
      opstack.push(infix[i]);

    // pops the stack until the corresponding left parenthesis is removed.
    // appends each operator popped to the end of the postfix string
    else if (infix[i] == ')') {

      while (!opstack.empty() && opstack.top() != '(') {
        postfix += opstack.top();
        postfix += ' ';
        opstack.pop();
      }
      if (!opstack.empty())
        opstack.pop();
    }

    else { // This is an operator
    
      // loop that pops all operators from the stack and appends them to the postfix string
      // untill the stack is empty or the operator on the stack has a lower precedence 
      // than the new operator toxen.
      while (!opstack.empty() && precedence(infix[i]) <= precedence(opstack.top())) {
          postfix += opstack.top();
          postfix += ' ';
          opstack.pop();
      }
      opstack.push(infix[i]);
    }
  }
  // appends the remaining operators from the stack to the postfix string
  while (!opstack.empty()) {
    postfix += opstack.top();
    postfix += ' ';
    opstack.pop();
  }

  return postfix;
}
/**
 * Gets the level of precedence for a given operator
 *
 * @param op: a character representation of an operator
 *
 * @return the operators numeric precedence 
 */
int precedence(char op) {
switch (op) {

    case '~':
    case '^':
      return 3;

    case '*':
    case '/':
      return 2;

    case '+':
    case '-':
      return 1;

    default:
      return -1;
  }
}
