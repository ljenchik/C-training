// Ex1.3 (powerpoint) Remove the join and sleep, do 100.000 iteration and 12 threads
// create cont=0 variable global, increment the value inside the for
// each thread print “I’m thread <arg> and my value is <cont>
// run the program many times, the result is always the same?

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int NTHREAD = 12;
int iterations = 100;
int cont = 0;

void *text(void *num)
{
  int threadNumber = *((int *)num);
  for (int i = 0; i < iterations; i++)
  {
    cont++;
    printf("I\'m thread %d and my value is %d\n", threadNumber, cont);
  }
  return NULL;
}

int main()
{
  pthread_t threads[12];
  int threadArgs[12];

  // Create threads
  for (int j = 0; j < 12; j++)
  {
    threadArgs[j] = j + 1;
    pthread_create(&threads[j], NULL, text, (void *)&threadArgs[j]);
    cont++;
  }

  // Join threads
  for (int i = 0; i < 12; i++)
  {
    threadArgs[i] = i + 1;
    pthread_join(threads[i], NULL);
  }

  return 0;
}