// Create a server Client application
// The client “register” to the server
// The server every 5 minutes sends the current time
// the client print the current time and “sleep” again
// do the version UDP, (Server register the client and after sends a UDP packet to all client)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 12345
#define BUFFER_SIZE 1024
// #define SERVER_IP "192.168.1.204"
#define SERVER_IP "127.0.0.1"

int main()
{
  int server_sd;
  struct sockaddr_in server_address, client_address;

  time_t rawtime;
  struct tm *timeinfo;

  // socklen_t client_addr_len = sizeof(client_address);
  socklen_t server_addr_len = sizeof(server_address);

  // Create UDP socket
  if ((server_sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Initialize server address
  memset(&server_address, 0, server_addr_len);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  // Bind socket to address and port
  if (bind(server_sd, (struct sockaddr *)&server_address, server_addr_len) == -1)
  {
    perror("Bind failed");
    close(server_sd);
  }

  printf("UDP Server is listening on port %d...\n", PORT);

  char buffer[BUFFER_SIZE];
  socklen_t client_addr_len = sizeof(client_address);

  // Receive data from the client
  int received_bytes = recvfrom(server_sd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &client_addr_len);
  if (received_bytes == -1)
  {
    perror("Receive failed");
  }
  printf("Client registration: %s \n", buffer);

  while (1)
  {
    // sendto(server_sd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_address, client_addr_len);
    // recvfrom(server_sd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &client_addr_len);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    memset(buffer, 0, BUFFER_SIZE);
    strftime(buffer, BUFFER_SIZE, "%c", timeinfo);
    printf("Current date and time: %s \n", buffer);

    sendto(server_sd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_address, client_addr_len);

    sleep(5);
  }

  close(server_sd);
  return 0;
}
