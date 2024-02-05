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
  int client_socket_1;
  struct sockaddr_in server_address;
  char buffer[BUFFER_SIZE];

  // Create client socket
  if ((client_socket_1 = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Initialize server address
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
  server_address.sin_port = htons(PORT);

  // Connect to server
  if (connect(client_socket_1, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
  {
    perror("Connection failed");
    close(client_socket_1);
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // Send a random number to the server
    const int rand_number = rand() % 90 + 1;
    printf("%d \n", rand_number);
    // Converting a random number to a string
    char str[20];
    sprintf(str, "%d", rand_number);
    int bytes_sent = send(client_socket_1, str, 20, 0);
    printf("%d \n", bytes_sent);

    // // Receive data from the server
    // memset(buffer, 0, sizeof(buffer));
    // int received_bytes = recv(client_socket_1, buffer, sizeof(buffer), 0);
    // if (received_bytes == 0)
    // {
    //   printf("Server disconnected\n");
    //   break;
    // }
    // printf("Received from server: %s\n", buffer);
    sleep(5);
  }

  close(client_socket_1);
  return 0;
}
