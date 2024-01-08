#include<stdio.h>
int main(void) {
  unsigned short int prot = 0xB7B2;

  printf("%d\n", prot);
  
  int type = prot >> 10;
  printf("Type: %d\n", type);

  int priority = ((unsigned short)(prot << 6)) >> 13;
  printf("Priority: %d\n", priority);

  int id = ((unsigned short)(prot <<9 )) >> 9;
  printf("ID: %d\n", id);

  // int check = (type << 10) + (priority << 7) + id;
  // printf("%d\n", check);


  // Conversion from base 10 to  base 2
  // int r;
  //     while(type!=0)
  //   {
  //       r=type%2;
  //       type=type/2;
  //       printf("%d\n", r);
  //   }

  // return 0;
}  