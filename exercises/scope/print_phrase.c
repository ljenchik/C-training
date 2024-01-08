// Write a program that pass a phrase to a function, and the function prints this phrase.
#include <stdio.h> 

void print_phrase(char phrase[]) {
  printf("%s\n", phrase);
}

int main(void) {
  char my_string[] = "Hello world!";
  print_phrase(my_string);
  return 0;
}

