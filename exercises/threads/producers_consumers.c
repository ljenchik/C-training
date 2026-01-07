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
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 4
#define NUM_CONSUMERS 4


pthread_mutex_t mutex;
int last_non_zero_index = -1;

int buffer[BUFFER_SIZE] = {0};

bool is_buffer_empty()
{
  return last_non_zero_index == -1;
}

bool is_buffer_full()
{
  return last_non_zero_index == BUFFER_SIZE - 1;
}

void print_buffer()
{
  printf("Buffer contains: ");
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    printf("%d ", buffer[i]);
  }
  printf("\n");
}

void add_to_buffer(int producer_id) {
    if (last_non_zero_index < BUFFER_SIZE - 1) {
        buffer[last_non_zero_index + 1] = rand() % 100 + 1;
        printf("[PRODUCER %d] adds %d to index %d\n", 
               producer_id, buffer[last_non_zero_index + 1], last_non_zero_index + 1);
        last_non_zero_index++;
        print_buffer();
    }
}

void remove_from_buffer(int consumer_id)
{
  if (last_non_zero_index >= 0)
  {
    printf("[CONSUMER %d] removes %d \n", 
               consumer_id, buffer[0]);
    buffer[0] = 0;
     for (int i = 0; i < BUFFER_SIZE - 1; i++) {
            buffer[i] = buffer[i + 1];
        }
        
      buffer[BUFFER_SIZE - 1] = 0;
    print_buffer();
    last_non_zero_index--;
  }
}

void *producer(void *args) {
    int id = *((int *)args);
    free(args);
    
    printf("[PRODUCER %d] Thread started\n", id);
    
    while (1) {
        pthread_mutex_lock(&mutex);
        
        if (!is_buffer_full()) {
            add_to_buffer(id);
        } else {
            printf("[PRODUCER %d] ⏸️  Buffer full, waiting...\n", id);
        }
        
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    
    return NULL;
}


void *consumer(void *args) {
    int id = *((int *)args);
    free(args);
    
    printf("[CONSUMER %d] Thread started\n", id);
    
    while (1) {
        pthread_mutex_lock(&mutex);
        
        if (!is_buffer_empty()) {
            remove_from_buffer(id);
        } else {
            printf("[CONSUMER %d] ⏸️  Buffer empty, waiting...\n", id);
        }
        
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    
    return NULL;
}

int main(void)
{
  pthread_t producers[NUM_PRODUCERS];
  pthread_t consumers[NUM_CONSUMERS];

  srand(time(NULL));

  // Initialize the mutex
  pthread_mutex_init(&mutex, NULL);

  printf("=== Producer-Consumer Problem ===\n");
  printf("Buffer Size: %d\n", BUFFER_SIZE);
  printf("Producers: %d | Consumers: %d\n\n", NUM_PRODUCERS, NUM_CONSUMERS);
    
    // Create producer threads
  for (int i = 0; i < NUM_PRODUCERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }

 for (int i = 0; i < NUM_CONSUMERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

  for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

  for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Clean up the mutex (only after threads finish)
    pthread_mutex_destroy(&mutex);
  // Clean up the mutex
  pthread_mutex_destroy(&mutex);

  return 0;
}

