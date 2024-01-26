
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

char *remove_leading_spaces(char *str, char *str1)
{
	int idx = 0, j, k = 0;
	while (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n')
	{
		idx++;
	}

	for (j = idx; str[j] != '\0'; j++)
	{
		str1[k] = str[j];
		k++;
	}
	str1[k] = '\0';
  printf("%s \n", str1);
  return str1;
}

char *remove_tailing_spaces(char *str, char *str2)
{
	int idx = strlen(str) - 1, j, k = 0;
	while (str[idx] == ' ')
	{
		idx--;
	}

	for (j = 0; j <= idx; j++)
	{
		str2[k] = str[j];
		k++;
	}
	str2[k] = '\0';
  printf("%s \n", str2);
  return str2;
}


int main()
{

	// file pointer
	FILE *fptr;
  char s[100];

	fptr = fopen("text_to_trim.txt", "r");

	// checking if the file is created
	if (fptr == NULL) {
		printf("The text_to_trim.txt is not found.");
    exit(0); 
	}
	else {
		while (fgets(s, 100, fptr) != EOF)
		{
			char *s1;
			remove_leading_spaces(s, s1);
			printf("%s\n", s1); 
		}
  }

	fclose(fptr);
	return 0;
}


