#include<stdio.h>
//Exercise 3, Create two pointers to two numbers and swap them ​

// int main() {
//   int a = 5;
//   int b = 8;
//   int *a_ptr = &a;
//   int *b_ptr = &b;

//   printf("a_ptr address %p\n", a_ptr);
//   printf("b_ptr address %p\n", b_ptr);

//   // creating a temporary pointer to a
//   int *temp_ptr = &a;
//   // changing a_pointer to b
//   a_ptr = &b;
//   // assigning b_pointer
//   b_ptr = temp_ptr;

//   printf("a_ptr = %d\n", *a_ptr);
//   printf("a_ptr address %p\n", a_ptr);

//   printf("b_ptr = %d\n", *b_ptr);
//   printf("b_ptr address %p\n", b_ptr);

//   return 0;
// }

int main () {
  int num1 = 3;
  int num2 = 7;

  int *num1_ptr = &num1;
  int *num2_ptr = &num2;

  printf("num1 address = %p, %p\n", num1_ptr, &num1);
  printf("num2 address = %p, %p \n", num2_ptr, &num2);

  int *temp_ptr = &num1;
  printf("temp value = %d, temp_ptr address = %p \n", *temp_ptr, temp_ptr);

  num1_ptr = &num2;
  printf("num1_ptr value = %d \n", *num1_ptr);
  
  num2_ptr = temp_ptr;
  printf("num2_ptr value = %d \n", *num2_ptr);

  printf("num1 = %d \n", num1);
  printf("num2 = %d \n", num2);

  printf("num1 address = %p, %p\n", num1_ptr, &num1);
  printf("num2 address = %p, %p \n", num2_ptr, &num2);

  return 0;
}