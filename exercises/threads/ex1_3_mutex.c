// Ex1_3 (using mutex)
// FIX YOUR PREVIOUSE EXERCISE 1.3, try to access to cont with a mutex. Run the programme many times, the issue has disappeared?

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

pthread_mutex_t mutex;

void *text(void *num)
{
  int threadNumber = *((int *)num);

  for (int i = 0; i < iterations; i++)
  {
    pthread_mutex_lock(&mutex);
    cont++;
    printf("I\'m thread %d and my value is %d\n", threadNumber, cont);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main()
{
  pthread_t threads[12];
  int threadArgs[12];
  pthread_mutex_init(&mutex, NULL);

  // Create threads

  for (int j = 0; j < 12; j++)
  {
    threadArgs[j] = j + 1;
    pthread_create(&threads[j], NULL, text, (void *)&threadArgs[j]);
  }

  // Join threads
  for (int i = 0; i < 12; i++)
  {
    threadArgs[i] = i + 1;
    pthread_join(threads[i], NULL);
  }

  return 0;
}