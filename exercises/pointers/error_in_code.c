//Find the errors in the code below. Could you explain your answer?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void  get_sky_team_name(char* name)
{
   char* ptr = (char*) malloc(20);
   //copy team name to pointer
   strcpy(*ptr, "Home Comms SW Team"); // malloc(10) is too low for this string
   //return team name
   
   name = ptr; // name = "Home Comms SW Team"

    free(ptr); // Better to free(ptr) in the main function
}
  
int main(void)
{
   char name[20];
   char* pTeamName = NULL;    
   
   strcpy(name, "Sky UK"); 
   printf("%s \n", name);    
   
   while(1) // indefinite loop
   {
       get_sky_team_name(pTeamName); // parameter is NULL 
       
       //print team name
       printf("%s: %s\n", name, pTeamName); // printf("%s: %s\n", name, pTeamName);
       
       sleep(1);
       free(pTeamName);
       pTeamName = NULL;
   }
   
  return 0;
}