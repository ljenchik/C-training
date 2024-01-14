// Ex1. Write a program to print individual characters of a string in reverse order
#include<stdio.h>
#include<string.h>

int main () {
  char my_string[] = "Hello world";
  // length of my_string
  int n = strlen(my_string);
  // declaring an array
  char arr[n];

  for (int i = n - 1; i >= 0; i--) {
    arr[i] = my_string[n -1 - i];
  }

  for (int i = 0; i < n; i++) {
    printf("%c\n", arr[i]);
  }

  printf("reverse string: %s\n", arr);
  return 0;
}

