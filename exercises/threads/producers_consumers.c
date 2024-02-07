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
#define BUFFER_SIZE 4

sem_t semaphore;
pthread_mutex_t mutex;

// int buffer[BUFFER_SIZE] = {1, 2, 3, 4};
int buffer[BUFFER_SIZE] = {1, 0, 0, 0};

bool is_buffer_empty(int buffer[BUFFER_SIZE])
{
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    if (buffer[i] != 0)
    {
      return false;
    }
  }
  return true;
}

bool is_buffer_full(int buffer[BUFFER_SIZE])
{
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    if (buffer[i] == 0)
    {
      return false;
    }
  }
  return true;
}

void print_buffer(int buffer[BUFFER_SIZE])
{
  printf("Buffer contains: ");
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    printf("%d ", buffer[i]);
  }
  printf("\n");
}

void add_to_buffer(int buffer[BUFFER_SIZE])
{
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    if (buffer[i] == 0)
    {
      srand(time(NULL));
      buffer[i] = rand() % 100 + 1;
      printf("Buffer is not full, producer adds %d to the buffer \n", buffer[i]);
      break;
    }
  }
  printf("Buffer after adding a new item");
  print_buffer(buffer);
}

void remove_from_buffer(int buffer[BUFFER_SIZE])
{
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    if (buffer[i] != 0)
    {
      printf("Buffer is not empty, consumer collects %d from the buffer \n", buffer[i]);
      buffer[i] = 0;
      break;
    }
  }
  printf("Buffer after collecting an item");
  print_buffer(buffer);
}

void *producers(void *args)
{
  printf("Thread producers started \n");
  while (1)
  {
    if (is_buffer_full(buffer) == false)
    {

      // Buffer is not full
      pthread_mutex_lock(&mutex);
      add_to_buffer(buffer);
      pthread_mutex_unlock(&mutex);
    }
    else
    {
      // Buffer is full
      // Producer waits for a space to add a new item
      printf("Buffer is full \n");
      sem_wait(&semaphore);
    }

    sem_post(&semaphore);
    sleep(2);
  }
  return NULL;
}

void *consumers()
{
  printf("Thread consumers started \n");
  if (is_buffer_empty(buffer) == true)
  {
    // Buffer is empty
    // Consumer waits for an item to collect
    printf("Buffer is empty \n");
    sem_wait(&semaphore);
  }
  else
  {
    // Buffer is not empty
    // Consumer collects the first non-zero item
    printf("Buffer is not empty, consumer collects from the buffer \n");
    pthread_mutex_lock(&mutex);
    remove_from_buffer(buffer);
    pthread_mutex_unlock(&mutex);
  }
  sem_post(&semaphore);
  sleep(2);
  return NULL;
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;

  sem_init(&semaphore, 0, 1);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&thread1, NULL, consumers, NULL);
  pthread_create(&thread2, NULL, producers, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  sem_destroy(&semaphore);

  return 0;
}
