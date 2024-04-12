#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <cstdio>
int main(int argc, char **argv){

  int output_file_descriptor, count;

  char *buffer; // message buffer.
  char* out_file; // holds file name.
  char cmflags[3]; // will hold -c flag, if used.

  //
  if (argc < 3) {
    std::cerr << "Usage: z200200 [-c] out_file message_string\n"
      << "where the message_string is appended to out_file.\n"
      << "The -c option clears the file before the message is appended";
    exit(EXIT_FAILURE);
  }
  
  // Get the args that have file name and message.
  if ((strcmp(argv[1], "-c")) == 0) {
    out_file = argv[2];
    buffer = argv[3];
    strcpy(cmflags, argv[1]);
  } else {
    out_file = argv[1];
    buffer = argv[2];
  }
  output_file_descriptor = open(out_file, O_WRONLY | O_CREAT, 0000);

  close(output_file_descriptor);

  // declares vars used by stat lib
  int stat_return_status;
  struct stat buf;

  // call stat function to populate our buffer
  stat_return_status = stat(out_file, &buf);

  // Checking for failure
  if (stat_return_status == -1) {
    std::cerr << out_file << ": Permission denied.";
    exit(EXIT_FAILURE);
  }
  // Checking permissions
  // if (buf.st_mode > 0) {
  if (!((buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXG)) == 0)) {

    std::cerr << out_file << ": is not secure. Ignoring.";
    exit(EXIT_FAILURE);
  }

  // Change permissions to allow writting by the user
  int rs; // return_status;
  rs = chmod(out_file, S_IWUSR);
  if (rs == -1) {
    std::cerr << "Unable to set write permission for the user";
    exit(EXIT_FAILURE);
  }
  // open the file for output 
  if (strcmp(cmflags, "") == 0) {
    output_file_descriptor = open(out_file, O_WRONLY | O_APPEND);
  } else if (strcmp(cmflags, "-c") == 0){
    output_file_descriptor = open(out_file, O_WRONLY | O_TRUNC);
  }
  // check for error with opening file
  if (output_file_descriptor == -1) {
    std::cerr << "Unable to open file";
    exit(EXIT_FAILURE);
  }
  rs = write(output_file_descriptor, buffer, strlen(buffer));
  rs = write(output_file_descriptor, "\n", strlen("\n"));
  if (rs == -1) {
    std::cerr << "Unable to write to file";
    exit(EXIT_FAILURE);
  }
  chmod(out_file, 0000);
  close(output_file_descriptor);
  return 0;
}
// PERMISSION
// st_mode & S_IRUSR  (owner has read permissions)
// st_mode & S_IWUSR  (write has write permissions)
// st_mode & S_IXUSR  (execute has read permissions)
// st_mode & S_IRWXU (owner has all permissions)
