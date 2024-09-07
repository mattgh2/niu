cmake_minimum_required(VERSION 3.20.0)
project(example) # Name whatever
# add_executable(test syscalls.cpp) 

# include_directories(./src)  # Libs (./src)
add_subdirectory(./src)  # Src Code (./src)

# TESTS
#add_subdirectory()  # Test dir
# enable_testing() 

