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
  int client_socket_2;
  struct sockaddr_in server_address;
  char buffer[BUFFER_SIZE];

  // Create client socket
  if ((client_socket_2 = socket(AF_INET, SOCK_STREAM, 0)) == -1)
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
  if (connect(client_socket_2, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
  {
    perror("Connection failed");
    close(client_socket_2);
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // Send a random number to the server
    // const int rand_number = rand() % 90 + 1;
    const char *message = "Hello, Server!";
    send(client_socket_2, message, strlen(message), 0);
    // send(client_socket_2, &rand_number, sizeof(int), 0);

    // Receive data from the server
    memset(buffer, 0, sizeof(buffer));
    int received_bytes = recv(client_socket_2, buffer, sizeof(buffer), 0);
    if (received_bytes == 0)
    {
      // Server disconnected
      printf("Server disconnected\n");
      break;
    }

    // Print received message
    printf("Received from server: %s\n", buffer);

    // Sleep for 5 seconds
    sleep(5);
  }

  // Close the socket
  close(client_socket_2);
  return 0;
}
