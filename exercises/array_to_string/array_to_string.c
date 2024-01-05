#include <stdio.h>

int main()
{

	char char_array[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0' };

	int i = 0;
  int length = sizeof(char_array)/sizeof(char_array[0]);
  // printf("%d\n", length);
	// while (i < length) {
  //   if (i == length - 2) {
  //     printf("%c\n", char_array[i]);
  //     break;
  //   }
  //   printf("%c", char_array[i]);
  //   i++;
	// }

  for (i = 0; i < length - 1; i++) {
      if (i == length - 2) {
      printf("%c\n", char_array[i]);
      break;
    }
    printf("%c", char_array[i]);
  }



	return 0;
}
