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
#include <semaphore.h>

struct database
{
  unsigned long long number_counter;
  unsigned long long last_prime_number;
  bool new_prime_number_found;
};

struct database Database = {10, 0, false};
sem_t semaphore;

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

void *thread1_function(void *args)
{
  Database.number_counter = *((unsigned long long *)args);
  for (unsigned long long i = 0; i < Database.number_counter; i++)
  {
    if (is_prime(i) == true)
    {
      if (Database.new_prime_number_found == false)
      {
        Database.last_prime_number = i;
        Database.new_prime_number_found = true;
        printf("Thread 1: last prime number is %llu \n", i);
        sem_post(&semaphore);
      }
      else
      {
        sem_wait(&semaphore);
        sleep(2);
      }
    }
  }
  return NULL;
}

void *thread2_function(void *args)
{
  Database.number_counter = *((unsigned long long *)args);
  for (unsigned long long i = 0; i < Database.number_counter; i++)
  {
    if (is_prime(i) == true)
    {
      printf("Thread 2: last prime number is %llu \n", i);
      Database.new_prime_number_found = false;
    }
    else
    {
      printf("Thread 2: current number is %llu \n", i);
    }
  }
  return NULL;
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;

  // Initializing semaphore, 0 for threads and 1 for processes, 1 is initial value of the semaphore
  sem_init(&semaphore, 0, 1);

  pthread_create(&thread1, NULL, thread1_function, (void *)&Database.number_counter);
  pthread_create(&thread2, NULL, thread2_function, (void *)&Database.number_counter);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  sem_destroy(&semaphore);
  return 0;
}
