// CLIENT CODE - Connects to server and receives time updates

#include <sys/types.h>      // Data types for system calls
#include <sys/socket.h>     // Socket functions (socket, connect, recv)
#include <arpa/inet.h>      // inet_pton
#include <netinet/in.h>     // sockaddr_in structure
#include <string.h>         // memset, strlen
#include <unistd.h>         // close, sleep
#include <stdio.h>          // printf
#include <stdlib.h>         // Standard library
#include <time.h>           // Time functions (not used in client)

int main()
{
  // === STEP 1: CREATE SOCKET ===
  // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = default protocol
  int cli_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (cli_sd < 0) {
      perror("Socket creation failed");
      exit(1);
  }
  
  struct sockaddr_in server_addr;  // Structure to hold server address
  char buffer[1024];               // Buffer to receive time string (1024 bytes)

  socklen_t ser_addr_len = sizeof(server_addr);  // Size of address structure

  // === STEP 2: CONFIGURE SERVER ADDRESS ===
  memset(&server_addr, 0, ser_addr_len);  // Zero out structure (clear garbage)
  server_addr.sin_family = AF_INET;       // Set address family to IPv4
  server_addr.sin_port = htons(1212);     // Set server port to 1212 (network byte order)
  
  // Convert IP "127.0.0.1" (localhost) from text to binary and store
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  // === STEP 3: CONNECT TO SERVER ===
  // Establish connection to server (blocks until connected)
  printf("Connecting to server...\n");
  if (connect(cli_sd, (struct sockaddr *)&server_addr, ser_addr_len) < 0) {
      perror("Connection failed");
      close(cli_sd);
      exit(1);
  }
  
  printf("Connected to server!\n");

  // === STEP 4: RECEIVE TIME FROM SERVER ===
  while (1)  // Infinite loop - keep receiving time
  {
    memset(buffer, 0, sizeof(buffer));  // Clear buffer (zero out old data)
    
    // Receive data from server (blocks until data arrives)
    // Returns number of bytes received
    int bytes = recv(cli_sd, buffer, sizeof(buffer) - 1, 0);

    if (bytes < 0) {
        perror("Receive failed");
        break;  // Exit loop on error
    } else if (bytes == 0) {
        printf("Server closed connection\n");
        break;  // Exit loop when server disconnects
    }

    buffer[bytes] = '\0';  // Null terminate
    printf("Received from the server: %s\n", buffer);
  }

  close(cli_sd);  // Close connection (never reached due to infinite loop)

  return 0;  // Never reached
}