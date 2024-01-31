// Ex1.1 (powerpoint) Main create NTHREAD=4, you give an integer  parameter <arg> the value start from 1 to NTHREADS
// Each thread run the same code and they print
// I’m thread <arg>
// they do 4 iteration
// The thread go to sleep for <arg> seconds
// The father after create the son call the pthread_exit(NULL)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int NTHREAD = 4;

void *text(void *num)
{
  int threadNumber = *((int *)num);
  printf("I\'m thread %d \n", threadNumber);

  return NULL;
}

int main()
{
  pthread_t threads[NTHREAD];
  int threadArgs[NTHREAD];

  // Create threads
  for (int i = 0; i < NTHREAD; i++)
  {
    threadArgs[i] = i + 1;
    pthread_create(&threads[i], NULL, text, (void *)&threadArgs[i]);
    sleep(threadArgs[i]);
  }

  // Join threads
  for (int i = 0; i < NTHREAD; i++)
  {
    threadArgs[i] = i + 1;
    pthread_join(threads[i], NULL);
  }

  return 0;
}