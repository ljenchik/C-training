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
   strcpy(pTeamName , "Home Comms SW Team");  // malloc is too low, should dallocate char *pTeamName = (char*) malloc(18) in line 8
   
   //print team name
   printf("%s: %s\n", skyName, pTeamName);
   free(pTeamName); // this line was missing
}

int main () {
   print_sky_team();
   return 0;
}

