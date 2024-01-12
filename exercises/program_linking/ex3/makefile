# Compile library files
lib_func.o: library_functions.c library_functions.h
	gcc -c library_functions.c -o lib_func.o
#Create static library. This step is to bundle multiple object files in one static library
lib_func.a: lib_func.o library_functions.c library_functions.h
	ar rcs lib_func.a lib_func.o
# Compile the main program
ex3.o : ex3.c library_functions.h library_functions.c
	gcc -c ex3.c -o ex3.o
# Link the compiled main program to the static library
ex3: ex3.o lib_func.a
	gcc -o ex3 ex3.o -L. lib_func.a
clean:
		-rm ex3 *.o *.a



# To run makefile: make
# To clean (to remove compilation_result): make clean
# To create a library run :
# gcc -c library_functions.c -o lib_func.o  
# ar rcs lib_func.a lib_func.o 