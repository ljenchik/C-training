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
#include <sys/types.h>
#include <pthread.h>

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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
  int server_socket, client_sockets[10];
  struct sockaddr_in server_address, client_address;

  socklen_t client_addr_len = sizeof(client_address);
  socklen_t server_addr_len = sizeof(server_address);

  int i = -1;

  char buffer[BUFFER_SIZE];

  int fd[2];
  pipe(fd);

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  bind(server_socket, (struct sockaddr *)&server_address, server_addr_len);

  // Prepare the server for incoming client requests
  // 10 is the maximum length for the queue of pending connections
  listen(server_socket, 10);

  printf("Server listening on port %d...\n", ntohs(server_address.sin_port));

  while (1)
  {
    // New connection
    int sd = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);

    printf("New connection, socket fd is %d, IP is : %s, port : %d\n", sd,
           inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    int pid;
    pid = fork();
    i++;
    if (pid == 0)
    {
      close(server_socket);
      close(fd[0]);
      memset(buffer, 0, sizeof(buffer));
      recv(sd, buffer, sizeof(buffer), 0);
      pthread_mutex_lock(&mutex);
      client_numbers[i].sd = sd;
      client_numbers[i].num = atoi(buffer);
      write(fd[1], client_numbers, sizeof(client_numbers));
      pthread_mutex_unlock(&mutex);
      printf("Clients numbers from socket %d: %s \n", sd, buffer);
      close(sd);
      exit(0);
    }
    wait(NULL);
    close(fd[1]);
    read(fd[0], client_numbers, sizeof(client_numbers));
    printf("Buffer contains %s \n", buffer);
  }
  for (int i = 0; i < 10; i++)
  {
    printf("hello");
    printf("Socket %d, number %d \n", client_numbers[i].sd, client_numbers[i].num);
  }
  return 0;
}
