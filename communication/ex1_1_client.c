// Create a server Client application
// TCP connection
// The client “register” to the server
// The server every 5 minutes sends the current time
// the client print the current time and “sleep” again

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  char buffer[1024] = {0};
  // Creating a server socket
  // SOCK_STREAM for TCP connection
  // AF_INET for IPv4, TCP and UDP protocols
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  // Creating a memory for it with 0 content
  memset(&server_addr, 0, sizeof(server_addr));
  // Initialising a socket
  server_addr.sin_family = AF_INET;
  // Translate an unsigned short integer into network byte order
  server_addr.sin_port = htons(1212);
  inet_pton(AF_INET, "192.168.1.204", &server_addr.sin_addr);

  connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  while (1)
  {
    // Receive and print the current time from the server
    memset(buffer, 0, sizeof(buffer));
    recv(sd, buffer, sizeof(buffer), 0);
    printf("Received from the server: %s \n", buffer);
    sleep(5);
  }

  close(sd);

  return 0;
}
