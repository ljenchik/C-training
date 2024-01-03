#include <stdio.h>
#include <stdlib.h>
int main()
{	
  char my_string[] = "1000";
  unsigned long n = strtoul(my_string, NULL, 10);
  printf("%lu\n", n);
	return 0;
}