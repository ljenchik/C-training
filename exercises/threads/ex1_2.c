// Ex1.2 (powerpoint) Change father thread that do the join to the second son and check if the operation has success

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
    if (threadArgs[i] == 2)
    {
      pthread_join(threads[i], NULL);
      printf("Successfully joined thread %d\n", threadArgs[1]);
    }
  }

  for (int i = 0; i < NTHREAD; i++)
  {
    if (i != 1)
    {
      pthread_join(threads[i], NULL);
    }
  }

  return 0;
}