// Server-Client lottery application.
// Draw how the processes interact with each other
// (client-server and inside the server,  any diagram is fine) of the following exercise.
// ( we will discuss it before you write the code)
// Every client connect to the server
// and gives a number (1 to 90) of the lottery.
// The server creates a process for each client (called client-process).
// The client-process communicate to a internal process that collect all the numbers.
// At a specific time the extractor process choose randomly a number.
// The process-client that has  won receive  a IPC message from the extractor process,
// and sends a message to the client. The clients will print if they won or not.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
  int ser_sd, cl_sd;
  struct sockaddr_in server_addr, client_addr;

  socklen_t cl_addr_len = sizeof(client_addr);
  socklen_t ser_addr_len = sizeof(server_addr);

  char buffer[BUFFER_SIZE];

  ser_sd = socket(AF_INET, SOCK_STREAM, 0);

  // Fills a block of memory with a 0
  memset(&server_addr, 0, ser_addr_len);

  // Initialising a socket
  server_addr.sin_family = AF_INET;

  // Translate an unsigned short integer into network byte order
  server_addr.sin_port = htons(PORT);

  inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
  // Assigns a server socket address to a socket identified by descriptor socket that has no local socket address assigned
  bind(ser_sd, (struct sockaddr *)&server_addr, ser_addr_len);

  // Prepare the server for incoming client requests
  // 10 is the maximum length for the queue of pending connections
  listen(ser_sd, 10);

  printf("Server listening on port %d...\n", ntohs(server_addr.sin_port));

  while (1)
  {
    if ((cl_sd = accept(ser_sd, (struct sockaddr *)&client_addr, &cl_addr_len)) < 0)
    {
      perror("Accept failed");
    }
    printf("Client connected\n");

    int received_bytes = recv(cl_sd, buffer, sizeof(buffer), 0);
    if (received_bytes == 0)
    {
      printf("Server disconnected\n");
      break;
    }
    printf("Received from client: %d\n", atoi(buffer));

    close(cl_sd);
  }

  return 0;
}
