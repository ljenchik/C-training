// Ex1 (wiki) Write a C programme:​

// The son process print a message like:​
// “I’m X, son of process Y” (X and Y are the PID and PPID)​
// The father print​
// “I’m the father. My Son is  : x”​

#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork();
  if (pid == 0)
  {
    printf("I\'m %d, son of process %d \n", getpid(), getppid());
  }
  else
  {
    printf("I\'m the father. My son is : %d\n", pid);
    printf("My pid is %d \n", getpid());
    printf("My ppid is %d \n", getppid());
  }
  return 0;
}