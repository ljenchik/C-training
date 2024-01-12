// Write a library that has multiple functions, where each function return the result of different equations. 
// Write a program that tests the library.

#include<stdio.h>
#include "library_functions.h"

int main(void) {
  printf("Rresult of add function is %d\n", func1(3));
  printf("Rresult of subtract function is %d\n", func2(8));
  printf("Rresult of multiply function is %d\n", func3(-8));
  return 0;
}