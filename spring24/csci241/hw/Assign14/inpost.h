#ifndef INPOST_H
#define INPOST_H

#include <string>
#include <cctype>
std::string convert(const std::string& infix);
int precedence(char op);
#endif
