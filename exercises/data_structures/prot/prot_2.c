//Consider that a 2 bytes variable Prot is composed of 3 fields (Type, Priority and ID) as shown below. 
// Write a program that prints the values of of these 3 fields (Type, Priority and ID) if Prot = 0xB7B2.
// Type 6 bits, Priority 3 bits, ID 7bits

#include<stdio.h>
#include <stdlib.h>
#include <math.h>

struct prot {
  unsigned char type: 6;
  unsigned char priority: 3;
  unsigned char id: 7;
};

int main(void) {
  unsigned short int prot = 0xB7B2;
  struct prot sp = {prot};

  printf("%d\n", sp.type);
  printf("%d\n", sp.priority);
  printf("%d\n", sp.id);
  
  return 0;
}  