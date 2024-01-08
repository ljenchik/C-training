#include <stdio.h>

float conversion(float a)
{
    return a * 9 / 5 + 32;
}

int main()
{	float c = 23.56;
    printf("%.2f\n", conversion(c));
	return 0;
}
