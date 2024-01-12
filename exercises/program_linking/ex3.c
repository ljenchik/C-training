#include<stdio.h>
#include "library_functions.h"

int main(void) {
  printf("Rresult of add function is %d\n", add(3, 8));
  printf("Rresult of subtract function is %d\n", subtract(3, 8));
  printf("Rresult of multiply function is %d\n", multiply(3, 8));
  printf("Rresult of divide function is %.2f\n", divide(3, 8));
  return 0;
}