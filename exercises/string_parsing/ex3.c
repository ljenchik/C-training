// Write a program to that counts the number of times a word is in a phrase.
#include<stdio.h>
#include<string.h>

int main () {
  char my_string[] = "Hello world world world hello";
  char my_word[] = "world";
  char *token = strtok(my_string, " ");
  int count = 0;
  while (token != 0) {
         if (strcmp(token, my_word) == 0) {
          count++;
         }
        token = strtok(0, " ");
    }
  
  if (count > 0) {
    printf("%d \n", count);
  }
  else {
     printf("A word is not found in a phrase\n");
  }
  
  return 0;
}