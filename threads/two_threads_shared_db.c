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
  while (true)
  {
    // pthread_mutex_lock(&mutex);
    while (Database.new_prime_number_found)
    {
      // pthread_mutex_lock(&mutex);
      sleep(5);
      // pthread_mutex_unlock(&mutex);
    }

    if (is_prime(Database.number_counter) == true)
    {
      pthread_mutex_lock(&mutex);
      if (Database.new_prime_number_found == true)
      {
        Database.last_prime_number = Database.number_counter;
        pthread_mutex_unlock(&mutex);
      };
    }
    Database.number_counter++;
    // pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *thread2_function()
{
  while (true)
  {
    pthread_mutex_lock(&mutex);
    if (Database.new_prime_number_found == true)
    {
      printf("Prime Number Found: %llu\n", Database.last_prime_number);
      Database.new_prime_number_found = false;
    }
    else
    {
      printf("Current Value: %llu\n", Database.number_counter);
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

// Thread1:

// 1. enter lock
// 2. set number_counter to i
// 3. exit lock
// 4. check if i is prime
// 5. repeat from 1 if i is not prime
// 6. enter lock
// 7. check flag new_prime_number_found. if true, exit lock, sleep repeat from 6.
// 8. if new_prime_number_found is false, set last_prime_number to i
// 9. exit lock
// 10. repeat from 1

// Thread 2:
// Loop forever
// 1. enter lock
// 2. check if number_counter is different from variable on stack, print is different
// 3. save number_counter on stack
// 4. check if new_prime_number_found is true, print last_prime_number if it's true
// 5. set new_prime_number_found to false
// 6. exit lock
// 7. repeat from 1.