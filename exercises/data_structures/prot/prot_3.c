//Consider that a 2 bytes variable Prot is composed of 3 fields (Type, Priority and ID) as shown below. 
// Write a program that prints the values of of these 3 fields (Type, Priority and ID) if Prot = 0xB7B2.
// Type 6 bits, Priority 3 bits, ID 7bits

#include<stdio.h>
int main(void) {
  unsigned short int prot = 0xB7B2;

// 1011011110110010 = 0xB7B2 = 47026
// prot >> 10 = 0000000000101101 = 45
  int type = prot >> 10;
  printf("Type: %d\n", type);

// prot >> 7 = 0000000101101111 
//       0x7 = 0000000000000111
// prot >> 7 & 0x7 = 0000000000000111 = 7
 int priority = prot >> 7 & 0x7;
  printf("Priority: %d\n", priority);


  // prot << 9 = 01100100000000
  // (prot << 9) >> 9 = 0000000000110010
  //             0x7f = 0000000001111111
  // (prot << 9) >> 9 & 0x7f = 0000000000110010 = 50
 //int id = (prot << 9) >> 9 & 0x7f;
  int id = prot & 0x7f;
  printf("Priority: %d\n", id);


  printf("%d\n", prot);
  
  

  return 0;
}  