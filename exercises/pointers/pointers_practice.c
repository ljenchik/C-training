#include<stdio.h>

int main (void) {
  int a = 12;
  printf("a = %d\n", a); 
  int *a_ptr = &a;
  // The indirection (*) operator is used to refer to the contents of the variable that the pointer points to
  // Changing the value/content of the variable a
  *a_ptr = 20;
  printf("a = %d, a_ptr = %p, *a_ptr = %d, &a = %p\n", a, a_ptr, *a_ptr, &a); 

  int num = 45;
  int *num_ptr = &num;
  int **num_ptr_ptr = &num_ptr;
  int ***num_ptr_ptr_ptr = &num_ptr_ptr;
  printf("num = %d, num address = %p, num_ptr = %p, num_ptr_ptr = %p, num_ptr_ptr_ptr = %p\n", num, &num, num_ptr, *num_ptr_ptr, **num_ptr_ptr_ptr);
  printf("num = %d, *num_ptr = %d, **num_ptr = %d, ***num_ptr_ptr_ptr = %d\n", num, *num_ptr, **num_ptr_ptr, ***num_ptr_ptr_ptr);


  return 0;
}