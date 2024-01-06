// An example of implicit conversion
#include <stdio.h>
int main()
{
	int x = 10; // integer x
	char y = 'a'; // character c

	// value of 'a' is 97
	
  x = x + y;
  y = x + y;

  printf("x = %d\n", x);
  printf("y = %d\n", y);

  printf("x = %c\n", x);
  printf("y = %c\n", y);

  //x is implicitly converted to float
	float z = x + 1;
	printf("x = %d, z = %.2f", x, z);

	return 0;
}
