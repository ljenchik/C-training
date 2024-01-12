int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
float divide(int a, int b);


// To create a library run :
// opo839@UKJ1Q01XFW5H program_linking % gcc -c library_functions.c -o lib_func.o  
// opo839@UKJ1Q01XFW5H program_linking % ar rcs lib_func.a lib_func.o 