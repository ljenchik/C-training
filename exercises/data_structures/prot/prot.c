//Consider that a 2 bytes variable Prot is composed of 3 fields (Type, Priority and ID) as shown below. 
// Write a program that prints the values of of these 3 fields (Type, Priority and ID) if Prot = 0xB7B2.
// Type 6 bits, Priority 3 bits, ID 7bits

#include<stdio.h>
int main(void) {
  unsigned short int prot = 0xB7B2;

  printf("%d\n", prot);
  
  // Shiting 10 cells to the right to get the first six numbers: 0000000000nnnnnn (6)
  int type = prot >> 10;
  printf("Type: %d\n", type);


  // Shifting 6 cells to th left to get the last 10 numbers: nnnnnnnnnn000000, then shifting to the right to get the middle three numbers: 00000000000000nnn (3)
  int priority = ((unsigned short)(prot << 6)) >> 13;
  printf("Priority: %d\n", priority);

  // Shifting 9 cells to the left: nnnnnnnnn0000000, then shifting back to get the last 7 numbers: 000000000nnnnnnn (7)
  int id = ((unsigned short)(prot <<9 )) >> 9;
  printf("ID: %d\n", id);

  // Checking the answer
  int check = (type << 10) + (priority << 7) + id;
  printf("%d\n", check);


  // Conversion from base 10 to  base 2
  int r;
      while(type!=0)
    {
        r=type%2;
        type=type/2;
        printf("%d\n", r);
    }

  return 0;
}  