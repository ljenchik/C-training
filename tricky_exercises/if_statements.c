#include <stdio.h>

int main(void)
{
   unsigned int    A = -10;
   int             B = 5;
   unsigned int    C = 100;
   
   if(A > B)
   {
       printf("A = %u, B =  %u ", A, B);
       printf("A > B\n");
   }
   else
   {
       printf("B > A\n");        
   }
   
   
   if(A > C)
   {
       printf("A = %u, C =  %u ", A, C);
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