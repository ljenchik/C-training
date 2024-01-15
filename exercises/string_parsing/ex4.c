// Write a program to sort a string array in ascending order.
#include<stdio.h>
#include<string.h>

int main () {
  char my_string[] = "simplyeasylearning";
  int n = strlen(my_string);
  char ch; 
    int i, j, l;

  for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (my_string[j] > my_string[j + 1]) { // Check if the current character is greater than the next one
                ch = my_string[j]; // Swap characters if they are out of order
                my_string[j] = my_string[j + 1];
                my_string[j + 1] = ch;
            }
        }
    }

  printf("sorted string: %s\n", my_string);
  return 0;
}