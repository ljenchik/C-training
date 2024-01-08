
//Write a program where you have 2 variables (A and B) initialised as zero, 
//this program should iterate 20 times, in each iteration you should increment "A" by 3 and "B" by 7. 
//The program should print the current values every 5 iterations and the last values, besides that, 
//the program should print A if it is an odd number, and print B if it is an even number.
#include<stdio.h>

int main(void) {
  int A = 0;
  int B = 0;

  for (int i = 0; i < 20; i++) {
    A += 3;
    B += 7;
    if (i != 0 && ((i + 1) % 5 == 0) ) {
      printf("%d iteration \n", i + 1);
      printf("A = %d\n", A);
      printf("B = %d\n", B);
    }
    else {
      printf("%d iteration \n", i + 1);
      if (A % 2 != 0) {
         printf("A = %d\n", A);
      }
      if (B % 2 == 0) {
        printf("B = %d\n", B);
      }
    }
    
  }


  return 0;
}
