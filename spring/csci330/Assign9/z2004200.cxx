#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

using std::string, std::vector;

void interpret();

int main(){

  interpret();
  return 0;
}

void interpret() {

  std::string command, arg;
  pid_t cpid;
  int rs;

  // primary read 
  std::cout << "Enter command: ";
  std::getline(std::cin, command); // gets input, stores in command string

  while (command != "exit") { // loops until users types exit

    vector<string> tmp_array; // temp storage for command input
    std::stringstream ss(command);
    int arg_count = 0;

    while (ss >> arg) {
      tmp_array.push_back(arg); // adds command/option/argument to temp storage
      arg_count++;
    }
    // error checking: user provided too many args. Terminates program
    if (arg_count > 5) {
      std::cerr << "Too many arguments/options. Please provide a maximum of 4 arguments/options\n";
      exit(EXIT_FAILURE);
    }

    
    // declaring new array of char *
    vector<char*> argv(arg_count + 1); 
    for (int i = 0; i < arg_count; i++) { // Converts string array to array of char * for execvp

      argv[i] = const_cast<char *>(tmp_array[i].c_str()); // Conversion method
    }

    // spawns a child process
    cpid = fork();

    // error checking: creating child process failed. Terminates program.
    if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    // child block
    if (cpid == 0) {
   
      // morphs child into new executable
      rs = execvp(argv[0], argv.data());

      // Error checking: exec failed
      if (rs == -1) {
        perror(argv[0]);
        exit(rs);

      } else { // kills child
        exit(rs);
      }

    // parent block 
    } else {
      wait(NULL); // waiting for child
      
      // continues with secondary read
      std::cout << "Enter command: ";
      std::getline(std::cin, command);
    }
  }
}
// pass in the command as a arg array of char*
