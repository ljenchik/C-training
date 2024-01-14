#include<stdio.h>
#include <string.h>

void print_sky_team(void)
{
   char skyName[10]; // declaration of a string, stores in a stack
   char *pTeamName = (char*) malloc(10); // allocates memoy in a heap, stores in a stack
   
   strcpy(skyName, "Sky UK");
   strcpy(pTeamName , "Home Comms SW Team"); 
       
   //print team name
   printf("%s: %s\n", skyName, pTeamName); 
}

int main () {
   print_sky_team();
   return 0;
}
