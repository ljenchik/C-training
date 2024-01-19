// Write a program that create a file and write your name inside.
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Counts a number of words in a string
int counter(char my_string[]) {
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
  return count;
}

int main()
{
	// file pointer
	FILE *fptr;
  char c;
  char s[100];
  int count = 0;

	// creating file (if doesn't exist) using "w" - open for writing in text mode
	fptr = fopen("text.txt", "r");

	// checking if the file is created
	if (fptr == NULL) {
		printf("The text.txt is not found.");
    exit(0); 
	}
	else {
    // Getting the first character from the file
    // c = fgetc(fptr);
    // printf("%c\n", c); // Prints L

    // Getting the first line from the file
    // fgets(s, 100, fptr);
    // printf("%s\n", s); // Prints Lorem Ipsum is simply dummy text of the printing and typesetting industry.
    

    // Printing all the lines in the file
    while(fgets(s, 100, fptr)) {
      count += counter(s);
    }
  }

printf("The number of words in the file is %d \n", count);
fclose(fptr);
return 0;
}



