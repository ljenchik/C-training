#include<stdio.h>
//Exercise 1, In a void function, add two values and then print that value in main​
// void add(int a, int b, int *result_pointer) {
//   *result_pointer = a + b;
// }

// int main () {
//   int result;
//   add(1, 6, &result);
//   printf("%d\n", result);
//   return 0;
// }


void add( int a, int b, int *sum) {
  *sum = a + b;
};

int main() {
  int a = 2;
  int b = 5;
  int result;
  add(a, b, &result);
  printf("result %d\n", result);
  return 0;
}






