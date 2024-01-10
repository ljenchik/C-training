#include<stdio.h> 
int main() 
{ 
unsigned int x = -1; 
printf("x = %d \n", x);
int y = ~0; 
printf("y = %d\n", y);

int z = ~1; 
printf("z = %d\n", z);

if (x == y) 
	printf("same \n"); 
else
	printf("not same \n"); 

  float a = 0.1;
  printf("%f", a);
    if ( a == 0.1f )
        printf("IF");
    else if (a == 0.1f)
        printf("ELSE IF");
    else
        printf("ELSE");
return 0; 
}



 
