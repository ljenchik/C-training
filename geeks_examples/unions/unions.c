#include<stdio.h>
#include<string.h>

union first_union {
    int num;
    char letter;
    int num_array[5];
};

int main(void) {
  
  union first_union union1;

  union1.num = 12;
  union1.letter = 'a';
  // It's not working
  // union1.num_array = {1, 2, 3, 4, 5};
  int arr[5] = {10, 2, 3, 4, 5};
  // Copy of int array
  memcpy(union1.num_array, arr, sizeof(arr));

  printf("%d\n", union1.num);
  printf("%c\n", union1.letter);


  for (int i = 0; i < 5; i++) {
    printf("%d\n", union1.num_array[i]);
  }
  

  int union1_size = sizeof(union1);

  printf("Sizeof union1: %d\n", union1_size);




  return 0;
}