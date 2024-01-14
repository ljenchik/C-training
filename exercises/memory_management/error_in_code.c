#include<stdio.h>
#include <string.h>
#include <stdlib.h> // this line was missing

void print_sky_team(void)
{
   char skyName[10]; // declaration of a string, is allocated in stack
   char *pTeamName = (char*) malloc(10); // allocates memory in a heap

   char arr2[13];
   char *pArr2;

   strcpy(skyName, "Sky UK"); 
   strcpy(pTeamName , "Home Comms SW Team");  //bug, malloc is too low
   
   //print team name
   printf("%s: %s\n", skyName, pTeamName);
   free(pTeamName); // missing line
}

int main () {
   print_sky_team();
   return 0;
}

