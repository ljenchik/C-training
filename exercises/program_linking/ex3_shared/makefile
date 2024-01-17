# Compile library files
lib_func.so: library_functions.c library_functions.h
	gcc -shared -fPIC -o lib_func.so library_functions.c
ex3: ex3.c library_functions.c library_functions.h
	gcc ex3.c -L. lib_func.so -o ex3
clean:
		-rm ex3 *.o *.a *.so


# gcc -shared -fPIC -o lib_func.so library_functions.c 
# gcc ex3.c -L. -llibrary -o ex3    
# export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH 
# -L. current directory
# ./ex3
#The flag-shared instructs the compiler that we are building a shared library. 
#The flag -fPIC is to generate position-independent code ???
#The option -L is a hint to the compiler to look in the directory 
#followed by the option for any shared libraries (during link-time only). 