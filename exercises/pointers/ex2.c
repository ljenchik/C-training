//Exercise 2, Create a function which takes two pointers to integers and swaps the values they are pointing to, 
//without changing the original memory of the two integers​
#include<stdio.h>

// void func(int *a_ptr, int *b_ptr) {
//   int temp_ptr = *a_ptr;
//   *a_ptr = *b_ptr;
//   *b_ptr = temp_ptr;
// }

// int main() {
//   int num1 = 4;
//   int num2 = 8;

//   printf("num1 address %p\n", &num1);
//   printf("num2 address %p\n", &num2);

//   func(&num1, &num2);
  
//   printf("num1 = %d\n", num1);
//   printf("num2 = %d\n", num2);

//   printf("num1 address %p\n", &num1);

//   printf("num2 address %p\n", &num2);
//   return 0;
// }


void swap(int **n1_ptr, int **n2_ptr) {
  //Make a temporary pointer to store the single dereference of n1_ptr
  int *temp = *n1_ptr;
  *n1_ptr = *n2_ptr;
  *n2_ptr = temp;
}

int main(void) {
  int num1 = 0;
  int num2 = 9;
  int *num1_ptr = &num1;
  int *num2_ptr = &num2;
  swap(&num1_ptr, &num2_ptr);
  printf("num1 = %d, num2 = %d, num1 = %d, num2 = %d \n", num1, num2, *num1_ptr, *num2_ptr);
  return 0;
}