#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>


int main(int argc, char **argv){
  int fd, count;
  char buffer[1024], filename[] = "example.txt";
  //open file
  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
  // read from file
  count = read(fd,buffer, 1024);
  std::cout << buffer;
  if (count == -1) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
  std::cout << "read " << count << " bytes from file\n";

  // close file
  close(fd);
  std::cout << "End of program";
  return 0;
}
