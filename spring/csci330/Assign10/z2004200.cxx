#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <string>

#include <sys/stat.h>
// /fileOne 
// / 
// TODO
void process_request(char **argv) {
     
}
int main(int argc, char **argv){

    int sock_fd;

    if (argc != 3) {
        std::cerr << "USAGE: z2004200 port path\n";
        exit(EXIT_FAILURE);
    }
    // TODO
    // Make sure a valid path was passed
    char *path = argv[2];
    if (path[0] != '/') {
        perror("Invalid path was recieved");
        exit(EXIT_FAILURE);
    }

    int rs;
    struct stat pathbuf;
    bool directory, file;

    rs = stat(path, &pathbuf); 
    if (rs == -1) {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    if (pathbuf.st_mode & S_IFDIR) {
        directory = true;
    }
    else if (pathbuf.st_mode & S_IFREG) {
        file = true;
    }
    else {
        perror("not a file or directory");
        exit(EXIT_FAILURE);
    }
    
  
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("Failed to create socket");
      exit(EXIT_FAILURE);
    }
    
    sockaddr_in server_address; 
    sockaddr_in client_address;
    unsigned int addrlen = sizeof(client_address);
   
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(atoi(argv[1]));
     
    if (bind(sock_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0)  {
      perror("bind");
      exit(EXIT_FAILURE);
    }

    if (listen(sock_fd,64) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }
    
    for (;;) {
      int newSock = accept(sock_fd, (sockaddr*)&client_address, &addrlen);
      if (newSock < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
      }
      if (fork()) {
        close(newSock);
      }
      else {
          process_request(argv);
      }
    }
    close(sock_fd);
    return 0;
}
