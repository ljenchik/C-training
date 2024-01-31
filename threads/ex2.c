// Ex2 (wiki) Write a C programme:
// Create a son process
// The son print “I’m the son Y” and terminate with the return status 1
// The father wait for the termination of the son, and after It will print the status of the terminated son
// Extra: Try to terminate the son in a involuntary way, and check if the son can detect it
// Change the programme that the father create N sons, and wait all the sons and print their status

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int st;
  int *status;
  status = &st;
  pid_t pid;
  for (int i = 0; i < 1; i++)
  {
    pid = fork();
  }
  if (pid == 0)
  {
    printf("I am the son %d, my status is: %d \n", getpid(), wait(status));
    exit(1);
  }
  else
  {
    wait(NULL);
  }
  return 0;
}