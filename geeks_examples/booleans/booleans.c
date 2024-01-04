#include <stdio.h>
// #include <stdbool.h>

typedef enum { false, true } bool;

int main()
{
	bool a = 1;
	bool b = 0;

  bool c = true;
	bool d = false;

	printf("True for a: %d\n", a);
	printf("False for b: %d\n", b);

  printf("True for c: %d\n", c);
	printf("False for d: %d\n", d);

	return 0;
}
