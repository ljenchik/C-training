#include<stdio.h>
#include<string.h>

int main() {


  // strlen ******************************************
  char my_string[] = "Hello World!";
  int length = strlen(my_string);
  printf("My_string length is %d \n", length);
  
  // strlen ******************************************
  int length1 = strlen("Be happy");
  printf("Be happy string length is %d \n", length1);

  // strcat ******************************************
  char first_string[50] = "I live in ";
  char second_string[] = "London";
  strcat(first_string, second_string); // first string is changing, the second string doesn't change
  printf("%s\n", first_string);
  printf("%s\n", second_string);

  // strncat ******************************************
  char third_string[50] = "I live in ";
  char fourth_string[] = "London";
  strncat(third_string, fourth_string, 3); // copies 3 first characters from the fourth_string to the third_string
  printf("%s\n", third_string);
  printf("%s\n", fourth_string);


  // strcopy ******************************************
  char new_string[20];
  char fifth_string[50] = "I live in London";
  strcpy(new_string, fifth_string); // copies one string to another
  printf("New_string is: %s\n",new_string);

  // strncopy ******************************************
  strncpy(new_string, my_string, 5); // copies 5 first characters from the my_string to the new_string
  printf("New_string is: %s\n",new_string);


  return 0;
}