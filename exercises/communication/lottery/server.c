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
#include <sys/select.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

// Array of structures go store random numbers from clients
struct cl_numbers
{
  int sd;
  int num;
};
struct cl_numbers client_numbers[10];

int main()
{
  int server_socket, client_sockets[10], max_sd;
  struct sockaddr_in server_address, client_address;
  fd_set read_fds; // adds the file descriptor fd to set

  socklen_t client_addr_len = sizeof(client_address);
  socklen_t server_addr_len = sizeof(server_address);
  char buffer[BUFFER_SIZE];

  // Clears (removes all file descriptors from) set
  FD_ZERO(&read_fds);

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  bind(server_socket, (struct sockaddr *)&server_address, server_addr_len);

  // Prepare the server for incoming client requests
  // 10 is the maximum length for the queue of pending connections
  listen(server_socket, 10);

  printf("Server listening on port %d...\n", ntohs(server_address.sin_port));

  for (int i = 0; i < 10; ++i)
  {
    client_sockets[i] = -1; // Initialize client sockets
  }

  while (1)
  {
    FD_SET(server_socket, &read_fds); // adds server socket to a set
    max_sd = server_socket;

    for (int i = 0; i < 10; ++i)
    {
      if (client_sockets[i] > 0)
      {
        FD_SET(client_sockets[i], &read_fds);
        if (client_sockets[i] > max_sd)
        {
          max_sd = client_sockets[i];
        }
      }
    }

    // Waits for activity on sockets
    // After select() has returned, read_fds will be cleared of
    // all file descriptors except for those that are ready for reading
    int activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
    if (activity == -1)
    {
      perror("Select error");
      exit(EXIT_FAILURE);
    }
    // New connection
    // FD_ISSET() returns nonzero if the file descriptor fd is present in set
    if (FD_ISSET(server_socket, &read_fds))
    {
      int new_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);
      if (new_socket == -1)
      {
        perror("Accept failed");
        exit(EXIT_FAILURE);
      }

      printf("New connection, socket fd is %d, IP is : %s, port : %d\n", new_socket,
             inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

      for (int i = 0; i < 10; ++i)
      {
        if (client_sockets[i] == -1)
        {
          client_sockets[i] = new_socket;
          break;
        }
      }
    }

    // Reading data from clients
    for (int i = 0; i < 10; i++)
    {
      int sd = client_sockets[i];
      int pid;
      pid = fork();
      if (pid == 0)
      {
        close(server_socket);
        if (FD_ISSET(sd, &read_fds))
        {
          memset(buffer, 0, sizeof(buffer));
          int received_bytes = recv(sd, buffer, sizeof(buffer), 0);
          printf("Received from client with socket_sd %d: %s\n", sd, buffer);
          client_numbers[i].sd = sd;
          client_numbers[i].num = atoi(buffer);
          printf("Clients numbers: %d, %d \n", client_numbers[i].sd, client_numbers[i].num);
        }
        close(sd);
        exit(0);
      }
    }
    wait(NULL);
    // printf("Client_numbers\n");
    //  for (int j = 0; j < 10; j++)
    //  {
    //    printf("%d, %d \n", client_numbers[j].sd, client_numbers[j].num);
    //  }
  }
  return 0;
}
