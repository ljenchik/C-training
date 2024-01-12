#include<stdio.h>
#include <string.h>

void print_sky_team(void)
{
   char skyName[10];
   char* pTeamName = (char*) malloc(10);
   
   strcpy(skyName, "Sky UK");
   strcpy(pTeamName , "Home Comms SW Team"); 
       
   //print team name
   printf("%s: %s\n", skyName, pTeamName); 
}

int main () {
   print_sky_team();
   return 0;
}
