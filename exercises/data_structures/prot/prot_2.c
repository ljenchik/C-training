//Consider that a 2 bytes variable Prot is composed of 3 fields (Type, Priority and ID) as shown below. 
// Write a program that prints the values of of these 3 fields (Type, Priority and ID) if Prot = 0xB7B2.
// Type 6 bits, Priority 3 bits, ID 7bits

#include<stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned char id: 7;
  unsigned char priority: 3;
  unsigned char type: 6;
  
} my_struct;


union u {
  int16_t num;
  my_struct my_struct;
} my_union;

int main(void) {
  my_union.num = 0xB7B2;
  
  printf("ID: %d\n", my_union.my_struct.id); 
  printf("Priority: %d\n", my_union.my_struct.priority); 
  printf("Type: %d\n", my_union.my_struct.type); 
  

  return 0;
}  