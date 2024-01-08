// Write a program that call a function 10 times, 
// each time this function must display a counter of how many times it was already used.
#include<stdio.h>


int my_function(void) {
  static int counter = 0;
  counter += 1;
  return counter;
}

int main(void) {
  for (int i = 0; i < 10; i++) {
    printf("my_function() was called %d times\n", my_function());
    
  }
  return 0;
}

