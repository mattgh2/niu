#
# PROGRAM:    Assignment 14
# PROGRAMMER: your name
# LOGON ID:   your z-id
# DATE DUE:   due date of program
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -ansi -std=c++14 -g 
        
# Rule to link object code files to create executable file
eval: main.o inpost.o eval.o mystack.o
	$(CXX) $(CXXFLAGS) -o eval $^

# Rules to compile source code file to object code
main.o: main.cpp inpost.h eval.h
inpost.o: inpost.cpp inpost.h mystack.h
eval.o: eval.cpp eval.h mystack.h
mystack.o: mystack.cpp mystack.h
 
# Pseudo-target to remove object code and executable files
clean:
	rm -f eval *.o
