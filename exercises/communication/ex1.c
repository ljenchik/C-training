// A parent creates 3 processes
// first child process prints a message and exit with code 0
// the others two children are in a infinite loop
// the father after 3 seconds send a signal SIGUSR1 to the children
// The children handle the message and print “received sig <sig>, from my parent  <pid>” and exit with code 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signum)
{
  printf("1 received sig %d, from my parent %d \n", signum, getppid());
  exit(1);
}

void signal_handler2(int signum)
{
  printf("2 received sig %d, from my parent %d \n", signum, getppid());
  exit(1);
}

void signal_handler3(int signum)
{
  printf("3 received sig %d, from my parent %d \n", signum, getppid());
  exit(1);
}

int main()
{
  pid_t pid1, pid2, pid3;
  / signal(SIGUSR1, signal_handler);

  pid1 = fork();
  if (pid1 == 0)
  {
    signal(SIGUSR1, signal_handler);
    printf("I am %d \n", getpid());
    exit(0);
  }

  pid2 = fork();
  if (pid2 == 0)
  {
    sleep(3);
    signal(SIGUSR1, signal_handler2);
    while (1)
    {
    }
  }

  pid3 = fork();
  if (pid3 == 0)
  {
    sleep(3);
    signal(SIGUSR1, signal_handler3);
    while (1)
    {
    }
  }

  sleep(3);

  kill(pid1, SIGUSR1);
  kill(pid2, SIGUSR1);
  kill(pid3, SIGUSR1);

  return 0;
}