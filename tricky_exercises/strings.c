#include<stdio.h>

void my_func(char *my_string) {
  printf("%s \n", my_string);
};

int main() {
  char my_string[] = "Hello";
  my_func(my_string);

	char str[20]; 
	char str1[20];
	// printf("Enter a string \n");
	// // taking input string 
	// scanf("%s: ", str); 

	printf("Enter a string \n");
	// using scanset in scanf to allow white spaces
    scanf("%[^\n]s", str1); 
  


	// printing the read string 
	printf("%s", str); 

  // printing read string 
    printf("%s", str1); 
  

  return 0;
};


