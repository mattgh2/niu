#
# PROGRAM:    Extra Credit Debugger Quiz
# PROGRAMMER: Kurt McMahon
# LOGON ID:   t90kjm1
#

# Compiler variablesa
CXX = g++
CXXFLAGS = -Wall -Werror -ansi -pedantic -std=c++14 -g

# Rule to link object code files to create executable file
quiz: quiz.o
	$(CXX) $(CXXFLAGS) -o quiz quiz.o

# Rules to compile source code files to object code
quiz.o: quiz.cpp

# Pseudo-target to remove object code and executable files
clean:
	rm -f *.o quiz
