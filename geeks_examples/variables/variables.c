// C program to demonstrate the 
// declaration, definition and
// initialization
#include <stdio.h>

// int main()
// {
// 	// declaration with definition
// 	int defined_var;

// 	printf("Defined_var: %d\n", defined_var);

// 	// initialization
// 	defined_var = 12;

// 	// declaration + definition + initialization
// 	int ini_var = 25;

// 	printf("Value of defined_var after initialization: %d\n",defined_var);
// 	printf("Value of ini_var: %d\n", ini_var);

// 	return 0;
// }


// C program to demonstrate use of static variable
// #include <stdio.h>

// void function()
// {
// 	int x = 20; // local variable
// 	static int y = 30; // static variable
// 	x = x + 10;
// 	y = y + 10;
// 	printf("\tLocal: %d\n\tStatic: %d\n", x, y);
// }

// int main()
// {
// 	printf("First Call\n");
// 	function();
// 	printf("Second Call\n");
// 	function();
// 	printf("Third Call\n");
// 	function();
//   printf("Fourth Call\n");
// 	function();
// 	return 0;
// }


// C program to demonstrate the problems
// in 'Macros'
#include <stdio.h>

#define var 5
int main()
{
	printf("%d ", var);

#ifdef var
#undef var

// redefine var as 10
#define var 10
#endif

	printf("%d\n", var);
	return 0;
}
