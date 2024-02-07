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
#include <time.h>
#define BUFFER_SIZE 4

sem_t semaphore;
pthread_mutex_t mutex;
int last_non_zero_index = -1; // the last non-zero element

// int buffer[BUFFER_SIZE] = {1, 2, 3, 4};
int buffer[BUFFER_SIZE] = {0};

bool is_buffer_empty(int buffer[BUFFER_SIZE])
{
  if (last_non_zero_index == 0)
  {
    return true;
  }
  return false;
}

bool is_buffer_full(int buffer[BUFFER_SIZE])
{
  if (last_non_zero_index == BUFFER_SIZE)
  {
    return true;
  }
  return false;
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
  if (last_non_zero_index < BUFFER_SIZE)
  {
    srand(time(NULL));
    buffer[last_non_zero_index + 1] = rand() % 100 + 1;
    printf("Buffer is not full, producer adds %d to the buffer at the place with index %d\n", buffer[last_non_zero_index + 1], last_non_zero_index + 1);
    last_non_zero_index = last_non_zero_index + 1;

    print_buffer(buffer);
  }
}

void remove_from_buffer(int buffer[BUFFER_SIZE])
{
  if (last_non_zero_index > 0)
  {
    printf("Buffer is not empty, consumer collects  %d from the place with index %d \n", buffer[last_non_zero_index], last_non_zero_index);
    buffer[last_non_zero_index] = 0;
    print_buffer(buffer);
    last_non_zero_index = last_non_zero_index - 1;
  }
}

// void *producers(void *args)
// {
//   printf("Thread producers started \n");
//   while (1)
//   {
//     if (is_buffer_full(buffer) == false)
//     {
//       // Buffer is not full
//       pthread_mutex_lock(&mutex);
//       add_to_buffer(buffer);
//       sleep(2);
//       pthread_mutex_unlock(&mutex);
//     }
//     else
//     {
//       // Buffer is full
//       // Producer waits for a space to add a new item
//       printf("Buffer is full \n");
//       sem_wait(&semaphore);
//     }
//     sem_post(&semaphore);
//     sleep(2);
//   }
//   return NULL;
// }

// void *consumers()
// {
//   printf("Thread consumers started \n");
//   while (1)
//   {
//     // sem_wait(&semaphore);
//     if (is_buffer_empty(buffer) == true)
//     {
//       // Buffer is empty
//       // Consumer waits for an item to collect
//       printf("Buffer is empty \n");
//       sem_wait(&semaphore);
//     }
//     else
//     {
//       // Buffer is not empty
//       // Consumer collects the first non-zero item
//       pthread_mutex_lock(&mutex);
//       remove_from_buffer(buffer);
//       sleep(2);
//       pthread_mutex_unlock(&mutex);
//     }
//     sem_post(&semaphore);
//     sleep(2);
//   }
//   return NULL;
// }

void *producers(void *args)
{
  printf("Thread producers started \n");
  while (1)
  {
    pthread_mutex_lock(&mutex);
    if (!is_buffer_full(buffer))
    {
      add_to_buffer(buffer);
    }
    pthread_mutex_unlock(&mutex);
    sleep(2);
  }
  return NULL;
}

void *consumers()
{
  printf("Thread consumers started \n");
  while (1)
  {
    pthread_mutex_lock(&mutex);
    if (!is_buffer_empty(buffer))
    {
      remove_from_buffer(buffer);
    }
    pthread_mutex_unlock(&mutex);
    sleep(2);
  }
  return NULL;
}

int main(void)
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
