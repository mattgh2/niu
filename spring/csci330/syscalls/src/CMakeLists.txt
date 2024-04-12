
add_executable(test syscalls.cpp) # Exe (main main.cpp)

configure_file(example.txt ${CMAKE_CURRENT_BINARY_DIR}/example.txt COPYONLY)
