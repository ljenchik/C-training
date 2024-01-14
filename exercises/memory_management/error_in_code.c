#include<stdio.h>
#include <string.h>
#include <stdlib.h> // this line was missing

void print_sky_team(void)
{
   char skyName[10]; // declaration of a string, is allocated in stack
   char *pTeamName = (char*) malloc(10); // allocates memory in a heap
   
   strcpy(skyName, "Sky UK"); // .text
   strcpy(pTeamName , "Home Comms SW Team");  // ./text
       
   //print team name
   printf("%s: %s\n", skyName, pTeamName);
}

int main () {
   print_sky_team();
   return 0;
}

