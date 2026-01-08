// Create a server Client application
// TCP connection
// The client “register” to the server
// The server every 5 minutes sends the current time
// the client print the current time and “sleep” again


#include <sys/types.h>      // Data types for system calls
#include <sys/socket.h>     // Socket functions (socket, bind, listen, accept)
#include <arpa/inet.h>      // inet_pton, inet_ntoa
#include <netinet/in.h>     // sockaddr_in structure
#include <string.h>         // memset, strlen
#include <unistd.h>         // close, sleep
#include <stdio.h>          // printf, perror
#include <stdlib.h>         // Standard library
#include <time.h>           // time, localtime, strftime

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

// SERVER CODE - Sends current time to connected clients

int main()
{
  int ser_sd, cl_sd;                          // Server and client socket descriptors
  struct sockaddr_in server_addr, client_addr; // Address structures for server and client
  socklen_t cl_addr_len = sizeof(client_addr);   // Size of client address structure
  socklen_t ser_addr_len = sizeof(server_addr);  // Size of server address structure
  char buffer[1024];          // Buffer to hold formatted time string
  time_t rawtime;             // Raw time value (seconds since epoch)
  struct tm *timeinfo;        // Struct to hold broken-down time

  // === STEP 1: CREATE SOCKET ===
  // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = default protocol
  ser_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (ser_sd < 0) {
    perror("Socket creation failed");
    exit(1);
  }

  // === STEP 2: CONFIGURE SERVER ADDRESS ===
  memset(&server_addr, 0, ser_addr_len);  // Zero out the structure (clear garbage)
  server_addr.sin_family = AF_INET;       // Set address family to IPv4
  server_addr.sin_port = htons(1212);     // Set port to 1212 (host to network byte order)
  
  // Convert IP "127.0.0.1" (localhost) to binary and store in sin_addr
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  // === STEP 3: BIND SOCKET TO ADDRESS ===
  // Associates socket with IP address and port
  if (bind(ser_sd, (struct sockaddr *)&server_addr, ser_addr_len) < 0) {
    perror("Bind failed");
    close(ser_sd);
    exit(1);
  }

  // === STEP 4: LISTEN FOR CONNECTIONS ===
  // Mark socket as passive (ready to accept connections)
  // 10 = max number of pending connections in queue
  if (listen(ser_sd, 10) < 0) {
    perror("Listen failed");
    close(ser_sd);
    exit(1);
  }

  printf("Server listening on port %d...\n", ntohs(server_addr.sin_port));

  // === STEP 5: ACCEPT AND SERVE CLIENTS ===
  while (1)  // Infinite loop - server runs forever
  {
    // Accept incoming connection (blocks until client connects)
    // Returns new socket descriptor for this client
    if ((cl_sd = accept(ser_sd, (struct sockaddr *)&client_addr, &cl_addr_len)) < 0)
    {
      perror("Accept failed");  // Print error if accept fails
    }
    printf("Client connected\n");

    // === STEP 6: SEND TIME TO CLIENT ===
    while (1)
    {
      time(&rawtime);
      timeinfo = localtime(&rawtime);
      
      printf("Sending time: %s", asctime(timeinfo));
      
      strftime(buffer, 1024, "%c", timeinfo);
      
      if (send(cl_sd, buffer, strlen(buffer), 0) < 0) {
        printf("Client disconnected\n");
        break;  // Exit inner loop
      }
      
      sleep(10);  
    }
    
    close(cl_sd); 
    printf("Client connection closed\n");
  }

  close(ser_sd); 
  return 0;
}