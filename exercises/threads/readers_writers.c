// Readers Writers Problem
// Suppose that a database is to be shared among several concurrent processes.
// Some of these processes may want only to read the database,
// whereas others may want to update (that is, to read and write) the database.
// We distinguish between these two types of processes by referring to the former
// as readers and to the latter as writers.
// Obviously, if two readers access the shared data simultaneously, no adverse effects will result.
// However, if a writer and some other process
// (either a reader or a writer) access the database simultaneously, chaos may ensue.
// To ensure that these difficulties do not arise, we require that the writers
// have exclusive access to the shared database while writing to the database.

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;
pthread_mutex_t mutex;

#include <stdio.h>

int is_file_empty(char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return -1;
  }
  // Move the file pointer to the end of the file
  fseek(file, 0, SEEK_END);
  // Get the current position of the file pointer
  long file_size = ftell(file);
  fclose(file);
  if (file_size == 0)
  {
    return 1; // File is empty
  }
  return 0; // File is not empty
}

int read_from_file(const char *filename)
{
  FILE *fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    perror("Error opening file");
    return -1;
  }
  char myString[100];
  while (fgets(myString, sizeof(myString), fptr) != NULL)
  {
    printf("%s", myString);
  }
  fclose(fptr);
  return 0;
}

int append_to_file(const char *filename, const char *data)
{
  FILE *fptr = fopen(filename, "a");
  fprintf(fptr, "%s \n", data);
  fclose(fptr);
  return 0;
}

void *readers()
{
  printf("Thread readers started \n");
  if (is_file_empty("text.txt") != 0)
  {
    printf("Thread readers can not read empty file \n");
    sem_wait(&semaphore);
    printf("Thread readers can read now \n");
    printf("File contains: ===============================\n");
    read_from_file("text.txt");
    printf("End of file: =================================\n");
    sem_post(&semaphore);
  }
  else
  {
    sem_wait(&semaphore);
    printf("Thread readers is reading from a file \n");
    printf("File contains: ===============================\n");
    read_from_file("text.txt");
    printf("End of file: =================================\n");
    sem_post(&semaphore);
  }
  return NULL;
}

void *writers(void *args)
{
  char *text_to_add = (char *)args;
  printf("Thread writers started \n");
  pthread_mutex_lock(&mutex);
  append_to_file("text.txt", text_to_add);
  printf("Thread writers successfully added to the file \n");
  pthread_mutex_unlock(&mutex);
  sem_post(&semaphore);
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

  pthread_create(&thread1, NULL, readers, NULL);
  pthread_create(&thread2, NULL, writers, "good day");
  pthread_create(&thread3, NULL, writers, "now");
  pthread_create(&thread4, NULL, readers, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);

  sem_destroy(&semaphore);

  return 0;
}
