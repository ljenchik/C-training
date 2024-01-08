#include <stdio.h>
#include <stdlib.h>
int main()
{	
  char my_string[] = "1000";
  unsigned long n = strtoul(my_string, NULL, 10);
  //unsigned long n2 = atol(my_string); unsafe function
  printf("%lu\n", n);
  //printf("%lu\n", n2);
	return 0;
}