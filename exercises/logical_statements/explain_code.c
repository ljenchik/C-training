#include <stdio.h>

int main(void)
{
   unsigned int    A = -10;
   int             B = 5;
   unsigned int    C = 100;
  


  // Unsigned integer range 0 to 4,294,967,295 
  // if unsigned int  = -10 it wraps 4,294,967,295 - 9 = 4294967286
   printf("A: %u\n", A);
   
  //  // if unsigned int  = -1 it wraps to the last number in the range 4,294,967,295
  //  unsigned int    D = -1;
  //  printf("A: %u\n", D);
   
   if(A > B)
   {
       printf("A > B\n");
   }
   else
   {
       printf("B > A\n");        
   }
   
   
   if(A > C)
   {
       printf("A > C\n");
   }
   else
   {
       printf("C > A\n");        
   }
   
   
   if(B > C)
   {
       printf("B > C\n");
   }
   else
   {
       printf("C > B\n");        
   }
   
  return 0;
}