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

int main()
{
  int ser_sd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_addr;
  char buffer[1024];

  socklen_t ser_addr_len = sizeof(server_addr);

  memset(&server_addr, 0, ser_addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(1212);
  inet_pton(AF_INET, "192.168.1.204", &server_addr.sin_addr);

  connect(ser_sd, (struct sockaddr *)&server_addr, ser_addr_len);

  while (1)
  {
    memset(buffer, 0, sizeof(buffer));
    recv(ser_sd, buffer, sizeof(buffer), 0);
    printf("Received from the server: %s \n", buffer);
    sleep(5);
  }

  close(ser_sd);

  return 0;
}
