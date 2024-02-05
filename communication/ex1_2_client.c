#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024
// #define SERVER_IP "192.168.1.204" ?????

int main()
{
  int client_socket;
  struct sockaddr_in server_address;
  char buffer[BUFFER_SIZE];
  socklen_t server_addr_len = sizeof(server_address);

  // Create UDP socket
  if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Initialize server address
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
  server_address.sin_port = htons(PORT);

  const char *message = "registered";
  sendto(client_socket, message, strlen(message), 0, (struct sockaddr *)&server_address, sizeof(server_address));

  while (1)
  {
    // Receive the echoed message from the server
    int received_bytes = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_address, &server_addr_len);
    if (received_bytes == -1)
    {
      perror("Receive failed");
      break;
    }

    printf("Received from server: %s \n", buffer);

    // memset(buffer, 0, BUFFER_SIZE);
    // sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_address, sizeof(server_address));

    sleep(5);
  }

  close(client_socket);
  return 0;
}
