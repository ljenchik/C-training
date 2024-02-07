// Producer Consumer Problem
// This problem is one of the small collection of standard,
//  well-known problems in concurrent programming:
//  a finite-size buffer and two classes of threads,
//  producers and consumers,
//  put items into the buffer (producers)
//  and take items out of the buffer (consumers).
//  A producer must wait until the buffer has space before it
//  can put something in, and a consumer must wait until
//  something is in the buffer before it can take something out.
//  A condition variable represents a queue of threads waiting
//  for some condition to be signalled.

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#define buffer_size 3

sem_t semaphore;
pthread_mutex_t mutex;

int buffer[buffer_size] = {1, 0, 3};

bool is_buffer_empty(int buffer[buffer_size])
{
  for (int i = 0; i < buffer_size; i++)
  {
    if (buffer[i] != 0)
    {
      return false;
    }
  }
  return true;
}

bool is_buffer_full(int buffer[buffer_size])
{
  for (int i = 0; i < buffer_size; i++)
  {
    if (buffer[i] == 0)
    {
      return false;
    }
  }
  return true;
}

void print_buffer(int buffer[buffer_size])
{
  printf("Buffer contains: ");
  for (int i = 0; i < buffer_size; i++)
  {
    printf("%d ", buffer[i]);
  }
  printf("\n");
}

void *producers(void *args)
{
  printf("Thread producers started \n");
  int item_to_add = *((int *)args);
  print_buffer(buffer);
  if (is_buffer_full(buffer) == false)
  {
    // Producer adds item to the buffer
    for (int i = 0; i < buffer_size; i++)
    {
      if (buffer[i] != 0)
      {
        buffer[i] = item_to_add;
        break;
      }
    }
  }
  else
  {
    sem_wait(&semaphore);
    for (int i = 0; i < buffer_size; i++)
    {
      if (buffer[i] != 0)
      {
        buffer[i] = item_to_add;
        break;
      }
    }
    sem_post(&semaphore);
  }
  return NULL;
}

void *consumers()
{
  printf("Thread consumers started \n");
  print_buffer(buffer);
  if (is_buffer_empty(buffer) == true)
  {
    sem_wait(&semaphore);
    // Consumer collects the first non-zero item
    for (int i = 0; i < buffer_size; i++)
    {
      if (buffer[i] != 0)
      {
        buffer[i] = 0;
        break;
      }
      sem_post(&semaphore);
    }
  }
  else
  {
    // Consumer collects the first non-zero item
    for (int i = 0; i < buffer_size; i++)
    {
      if (buffer[i] != 0)
      {
        printf("Consumer collected %d \n", buffer[i]);
        buffer[i] = 0;
        print_buffer(buffer);
        break;
      }
    }
  }
  return NULL;
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  pthread_t thread4;

  sem_init(&semaphore, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&thread1, NULL, consumers, NULL);
  // pthread_create(&thread2, NULL, consumers, NULL);
  int *num = malloc(sizeof(int));
  pthread_create(&thread3, NULL, producers, (void *)num);
  // pthread_create(&thread4, NULL, producers, 9);

  pthread_join(thread1, NULL);
  // pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  // pthread_join(thread4, NULL);

  sem_destroy(&semaphore);

  return 0;
}
