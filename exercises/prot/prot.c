#include<stdio.h>
int main(void) {
  unsigned short int Prot = 0xB7B2;
  
  int id1 = Prot >> 13;
  printf("%d\n", Prot);
  printf("%d\n", id1);

  int id2 = ((unsigned short)(Prot << 3)) >> 10;
  printf("%d\n", id2);
  
  int id3 = ((unsigned short)(Prot <<9 )) >> 9;
  printf("%d\n", id3);

  int check = (id1 << 13) + (id2 << 7) + id3;
  printf("%d\n", check);
  return 0;
}  