#include <stdio.h> 
#include <string.h> 

struct struct_example { 
	int integer; 
	float decimal; 
	char name[20]; 
}; 

union union_example { 
	int integer; 
	float decimal; 
	char name[20]; 
}; 

int main(void) 
{ 
	struct struct_example s = { 18, 38, "geeksforgeeks" }; 
	union union_example u;
  u.integer = 18;
  u.decimal = 38;
  strcpy(u.name, "geeksforgeeks"); 

	printf("structure data:\n integer: %d\n"
		"decimal: %.2f\n name: %s\n", 
		s.integer, s.decimal, s.name); 

	printf("\nunion data:\n integer: %d\n"
		"decimal: %.2f\n name: %s\n", 
		u.integer, u.decimal, u.name); 

	// Size of structure and union 
	printf("\nsizeof structure : %lu\n", sizeof(s)); 
	printf("sizeof union : %lu\n", sizeof(u)); 

	printf("\n Accessing all members at a time:"); 
	s.integer = 183; 
	s.decimal = 90; 
	strcpy(s.name, "geeksforgeeks"); 

	printf("structure data:\n integer: %d\n "
		"decimal: %.2f\n name: %s\n", 
		s.integer, s.decimal, s.name); 

	u.integer = 183; 
	u.decimal = 90; 
	strcpy(u.name, "geeksforgeeks"); 

	printf("\nunion data:\n integer: %d\n "
		"decimal: %.2f\n name: %s\n", 
		u.integer, u.decimal, u.name); 

	// printf("\n Accessing one member at time:"); 

	// printf("\nstructure data:"); 
	// s.integer = 240; 
	// printf("\ninteger: %d", s.integer); 

	// s.decimal = 120; 
	// printf("\ndecimal: %f", s.decimal); 

	// strcpy(s.name, "C programming"); 
	// printf("\nname: %s\n", s.name); 

	// printf("\n union data:"); 
	// u.integer = 240; 
	// printf("\ninteger: %d", u.integer); 

	// u.decimal = 120; 
	// printf("\ndecimal: %f", u.decimal); 

	// strcpy(u.name, "C programming"); 
	// printf("\nname: %s\n", u.name); 

	// // difference four 
	// printf("\nAltering a member value:\n"); 
	// s.integer = 1218; 
	// printf("structure data:\n integer: %d\n "
	// 	" decimal: %.2f\n name: %s\n", 
	// 	s.integer, s.decimal, s.name); 

	// u.integer = 1218; 
	// printf("union data:\n integer: %d\n"
	// 	" decimal: %.2f\n name: %s\n", 
	// 	u.integer, u.decimal, u.name); 
  return 0;
}
