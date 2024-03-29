#
# PROGRAM:    Assignment 13
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14 -g
        
# Rule to link object code files to create executable file
stack_test: stack_test.o mystack.o
	$(CXX) $(CXXFLAGS) -o stack_test $^

# Rules to compile source code file to object code
stack_test.o: stack_test.cpp mystack.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f stack_test *.o
