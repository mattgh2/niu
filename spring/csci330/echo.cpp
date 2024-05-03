#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

int main(int argc, char **argv){

  if (argc != 4) {
    std::cerr << "USAGE: echoClient server_ip port message\n";
    exit(EXIT_FAILURE);
  }
  char buffer[256]; // our message buffer
  int echolen, received = 0;
  
  int sock; // socket fd
  sockaddr_in server_address; // structure for address of server (sock_addr)
  unsigned int addrlen = sizeof(server_address);
  
  // Create the UDP socket
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  }
  // Construct the server sockaddr_in structure 
  memset(&server_address, 0, sizeof(server_address));     /* Clear struct */
  server_address.sin_family = AF_INET;                    /* Internet/IP */
  server_address.sin_addr.s_addr = inet_addr(argv[1]);    /* IP address */
  server_address.sin_port = htons(atoi(argv[2]));         /* Server port */
  
  // Send the message to the server
  echolen = (strlen(argv[3]) + 1); // One more for null terminator
  if (sendto(sock, argv[3], echolen, 0, (struct sockaddr *) &server_address, sizeof(server_address))) {
    perror("sendto");
    exit(EXIT_FAILURE);
  }
  // receive the message back from the server
  if ((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) & server_address, &addrlen)) != echolen) {
    perror("recvfrom");
    exit(EXIT_FAILURE);
  }

  std::cout << "Server (" << inet_ntoa(server_address.sin_addr) << ") echoed: " << received << " bytes: " << buffer << std::endl;

  close(sock);

  

  return 0;
}
