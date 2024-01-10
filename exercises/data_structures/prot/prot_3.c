//Consider that a 2 bytes variable Prot is composed of 3 fields (Type, Priority and ID) as shown below. 
// Write a program that prints the values of of these 3 fields (Type, Priority and ID) if Prot = 0xB7B2.
// Type 6 bits, Priority 3 bits, ID 7bits

#include<stdio.h>
int main(void) {
  unsigned short int prot = 0xB7B2;

  int type = prot >> 10;
  printf("Type: %d\n", type);


 int priority = prot >> 7 & 0x7;
  printf("Priority: %d\n", priority);

  
 int id = (prot << 9) >> 9 & 0x7f;
  printf("Priority: %d\n", id);


  printf("%d\n", prot);
  
  

  return 0;
}  