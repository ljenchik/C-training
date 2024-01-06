#include<stdio.h>
int main(void) {
  int Prot = 0xB7B2;
  
  // id = prot >> (sizeof(int) - 7)
  printf("%d\n", Prot);

  return 0;
}