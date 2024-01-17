#include<stdio.h> 
int main() 
{ 
unsigned short int x = -1; 
printf("x = %hu \n", x);
printf("x = %d \n", x);

unsigned int l = -1; 
printf("l = %u \n", l);
printf("l = %d \n", l);


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



 
