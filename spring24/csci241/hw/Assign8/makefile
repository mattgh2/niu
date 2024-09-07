#
# PROGRAM:    Assignment 8
# PROGRAMMER: Matt Warner
# LOGON ID:   z2004200
# DATE DUE:   2/20/24
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14 -g
        
# Rule to link object code files to create executable file
simplesim: main.o simplesim.o
	$(CXX) $(CXXFLAGS) -o simplesim $^

# Rules to compile source code file to object code
main.o: main.cpp simplesim.h
simplesim.o: simplesim.cpp simplesim.h sml.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f simplesim *.o
