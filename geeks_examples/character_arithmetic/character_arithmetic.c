#include <stdio.h>

int main()
{
	char ch1 = 125, ch2 = 10;
	ch1 = ch1 + ch2; // 125 + 10 = 127 + 8 = -128 -127 ... -121 wraps to negatives
	printf("%d\n", ch1);
	printf("%c\n", ch1 - ch2 - 4); // -121 - 10 - 4 = -128 - 3 - 4 = 127 126 ... 121 wraps to positives
	return 0;
}
