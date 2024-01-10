//Consider that a 2 bytes variable Prot is composed of 3 fields (Type, Priority and ID) as shown below. 
// Write a program that prints the values of of these 3 fields (Type, Priority and ID) if Prot = 0xB7B2.
// Type 6 bits, Priority 3 bits, ID 7bits

#include<stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  unsigned short int prot = 0xB7B2;
  printf("%d\n", prot);
  int r;
  int i = 0;


  // Converting base 16 to binary representation
  int binary_array[16];
  while(prot!=0) {
        r=prot%2;
        prot=prot/2;
        binary_array[15 - i] = r;
        i++;
  };

  for (int i = 0; i < 16; i++) {
    printf("%d", binary_array[i]);
  }

  char type_array[6];
  int priority_array[3];
  int id_array[7];

  // Type binary array
  for (int i = 0; i < 6; i++) {
    type_array[i] = binary_array[i];
  }

  // Priority binary array
  for (int i = 0; i < 3; i++) {
    priority_array[i] = binary_array[6 + i];
  }

  // ID binary array
  for (int i = 0; i < 7; i++) {
    id_array[i] = binary_array[9 + i];
  }

  int type_value = 0;
  for (int i = 0; i < 6; i++) {
    type_value += pow(2, 5 - i) * (int)type_array[i];
  }
  printf("\n Type %d", type_value);

  int priority_value = 0;
  for (int i = 0; i < 3; i++) {
    priority_value += pow(2, 2 - i) * (int)priority_array[i];
  }
  printf("\n Priority %d", priority_value);

  int id_value = 0;
  for (int i = 0; i < 7; i++) {
    id_value += pow(2, 6 - i) * (int)id_array[i];
  }
  printf("\n ID %d \n", id_value);

  return 0;
}  