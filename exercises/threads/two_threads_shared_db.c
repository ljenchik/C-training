// Ex1 (wiki) Write a code that has 2 threads and a shared database.
// The Database must contain:
// unsigned long long  number_counter;
// unsigned long long  last_prime_number;
// bool new_prime_number_found;
// Thread 1: Must check all the numbers starting from 0 if it is a prime number,
// if so, it must write the value in last_prime_number and raise the flag new_prime_number_found.
// However if the new_prime_number_found flag is already raised, the thread must wait.
// Thread 2: Must print ALL the prime numbers found and
// must print the current value being tested if nothing was printed in the last 5 seconds.
// The prime numbers must be printed in a different way.

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

struct database
{
  unsigned long long number_counter;
  unsigned long long last_prime_number;
  bool new_prime_number_found;
};

struct database Database = {0, 0, false};
pthread_mutex_t mutex;

bool is_prime(unsigned long long num)
{
  if (num <= 1)
  {
    return false;
  }
  for (unsigned long long i = 2; i <= sqrt(num); i++)
  {
    if (num % i == 0)
    {
      return false;
    }
  }
  return true;
}

void *thread1_function()
{
  printf("Thread 1: starting thread 1\n");
  sleep(2);
  while (true)
  {
    // printf("Thread 1: starting thread 1 inside first loop \n");
    sleep(2);
    pthread_mutex_lock(&mutex);
    // printf("Thread 1: number_counter %llu \n", Database.number_counter);
    sleep(2);

    while (Database.new_prime_number_found)
    {
      pthread_mutex_lock(&mutex);
      sleep(2);
      pthread_mutex_unlock(&mutex);
    }

    if (is_prime(Database.number_counter) == true)
    {
      // printf("Thread 1: number_counter inside first if %llu \n", Database.number_counter);
      if (Database.new_prime_number_found == true)
      {
        sleep(2);
        Database.new_prime_number_found = false;
      }
      else
      {
        // pthread_mutex_lock(&mutex);
        Database.last_prime_number = Database.number_counter;
        Database.new_prime_number_found = true;
        // pthread_mutex_unlock(&mutex);
      }
    }
    Database.number_counter++;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

void *thread2_function()
{
  printf("Thread 2: starting thread 2 \n");
  sleep(2);
  while (true)
  {
    // printf("Thread 2: starting thread 2 inside first loop\n");
    sleep(2);
    pthread_mutex_lock(&mutex);
    // printf("Thread 2: number_counter %llu \n", Database.number_counter);
    sleep(2);
    if (Database.new_prime_number_found == true)
    {
      printf("Thread 2: prime number found: %llu\n", Database.last_prime_number);
      Database.new_prime_number_found = false;
    }
    else
    {
      printf("Thread 2: current number_counter: %llu\n", Database.number_counter);
      sleep(2);
    }
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&thread1, NULL, thread1_function, NULL);
  pthread_create(&thread2, NULL, thread2_function, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
