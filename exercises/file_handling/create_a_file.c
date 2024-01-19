// Write a program that create a file and write your name inside.
#include <stdio.h>
#include <stdlib.h>

int main()
{
	// file pointer
	FILE *fptr;

	// creating file (if doesn't exist) using "w" - open for writing in text mode
	fptr = fopen("name.txt", "w");

	// checking if the file is created
	if (fptr == NULL) {
		printf("The name.txt is not opened.");
	}
	else {
    fputs("My name is Olena \n", fptr);
    fprintf(fptr, "Today's date is %s \n",  __DATE__);
    fprintf(fptr, "Current time is %s \n",  __TIME__);
	}
  fclose(fptr);
	return 0;
}



