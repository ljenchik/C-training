#include <stdio.h>
#include <pthread.h> // posix thread library

// Function has to return a void pointer
void *computation(void *num)
{
  // casting int type to a void pointer
  long sum = 0;
  int *num_conv = (int *)num;
  for (long i = 0; i < 1000000000; i++)
  {
    sum += *num_conv;
  }
  printf("Computation is %ld \n", sum);
  return NULL;
}

int main()
{
  pthread_t thread1;
  pthread_t thread2;
  long value1 = 1;
  long value2 = 2;
  // Pointer to the thread, function, arguments to the function
  pthread_create(&thread1, NULL, computation, (void *)&value1);
  pthread_create(&thread2, NULL, computation, (void *)&value2);
  // Joining main after execution
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}