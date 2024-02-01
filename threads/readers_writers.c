// Readers Writers Problem
// Suppose that a database is to be shared among several concurrent processes.
// Some of these processes may want only to read the database,
// whereas others may want to update (that is, to read and write) the database.
// We distinguish between these two types of processes by referring to the former
// as readers and to the latter as writers.
// Obviously, if two readers access the shared data simultaneously,
// no adverse effects will result.
// However, if a writer and some other process
// (either a reader or a writer) access the database simultaneously, chaos may ensue.
// To ensure that these difficulties do not arise, we require that the writers
// have exclusive access to the shared database while writing to the database.
// This synchronization problem is referred to as the readers-writers problem.

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>

struct database
{
  int year;
  int date;
  int month;
  int age;
};

pthread_mutex_t mutex;
struct database Database = {2024, 23, 12, 8};

void *readers()
{
  printf("Year: %d, Month: %d, Date: %d, Age: %d \n", Database.year, Database.month, Database.date, Database.age);
  return NULL;
}

void *writers()
{
  pthread_mutex_lock(&mutex);
  Database.year += 1;
  Database.month += 1;
  Database.date += 1;
  Database.age += 1;
  pthread_mutex_unlock(&mutex);
  printf("Year: %d, Month: %d, Date: %d, Age: %d \n", Database.year, Database.month, Database.date, Database.age);
  return NULL;
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&thread1, NULL, readers, NULL);
  pthread_create(&thread2, NULL, readers, NULL);
  pthread_create(&thread3, NULL, writers, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
