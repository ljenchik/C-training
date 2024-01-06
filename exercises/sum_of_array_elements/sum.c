#include<stdio.h>
int main() {
	int num_array[5] = {1, 2, 36, 4, -5};
  float sum = 0;
  int length = sizeof(num_array)/sizeof(int);
  
  int i;
  for (i = 0; i < length; i++) {
    sum = sum + num_array[i];
  }

  float average = sum / length;

  printf("Sum of the array is %.2f\n", sum);
  printf("Average of the array is %.2f\n", average);

	return 0;
}
