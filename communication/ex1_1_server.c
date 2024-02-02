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

// struct sockaddr_in
// {
//   sa_family_t sin_family;  // family address: AF_INET
//   in_port_t sin_port;      // port in network byte order
//   struct in_addr sin_addr; // internet address
// };

// struct in_addr
// {
//   unit32_t s_addr; // address in network byte order
// };

int main()
{
  int ser_sd, cl_sd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[1024];
  time_t rawtime;
  struct tm *timeinfo;

  // Creating a server socket
  // SOCK_STREAM for TCP connection
  // AF_INET for IPv4, TCP and UDP protocols
  ser_sd = socket(AF_INET, SOCK_STREAM, 0);
  // Deslaring a socket
  // Creating a memory for it with 0 content
  memset(&server_addr, 0, sizeof(server_addr));
  // Initialising a socket
  server_addr.sin_family = AF_INET;
  // Translate an unsigned short integer into network byte order
  server_addr.sin_port = htons(1212);
  inet_pton(AF_INET, "192.168.1.204", &server_addr.sin_addr);
  // The bind() function assigns a server socket address to a socket identified by descriptor socket that has no local socket address assigned.
  bind(ser_sd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(ser_sd, 10);
  printf("Server listening on port %d...\n", server_addr.sin_port);
  while (1)
  {
    // Accept the incoming connection
    int len = sizeof(client_addr);
    if ((cl_sd = accept(ser_sd, (struct sockaddr *)&client_addr, &len)) < 0)
    {
      perror("Accept failed");
    }
    printf("Client connected\n");
    while (1)
    {
      time(&rawtime);
      timeinfo = localtime(&rawtime);
      printf("Curren time and date: %s", asctime(timeinfo));
      // Formats the time represented and stored into buffer
      strftime(buffer, 1024, "%c", timeinfo);
      send(cl_sd, buffer, strlen(buffer), 0);
      sleep(10);
    }
    close(cl_sd);
  }

  return 0;
}
