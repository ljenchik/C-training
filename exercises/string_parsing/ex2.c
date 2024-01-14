// Write a program to count the total number of words in a string.
#include<stdio.h>
#include<string.h>

int main () {
  char my_string[] = "Hello world, I am learning C";
  char *token = strtok(my_string, " ");
  int count = 0;
  while (token != 0) {
         //strtok writes a '\0' where it finds the token you supplied, 
         // and returns a pointer to the start of the string. 
         // Internally it maintains the location of the last token; 
         //and next time you call it, it starts from there.
        token = strtok(0, " ");
        count++;
    }
 
  printf("The total number of words in a string is %d \n", count);
  return 0;
}
