# Shared library
# Creating a shared library
linked_list_library.so: linked_list_operations.c linked_list_operations.h
	gcc -shared -fPIC -o linked_list_library.so linked_list_operations.c

# Compile the linked_list.c file
linked_list: linked_list.c linked_list_operations.c linked_list_operations.h
	gcc linked_list.c -L . linked_list_library.so -o linked_list


clean: 
		-rm linked_list *.o *.a *.so




# # Static library
# # Compile library files
# linked_list_library.o: linked_list_operations.c linked_list_operations.h
# 	gcc -o linked_list_library.o -c linked_list_operations.c

# # Create static library
# linked_list_library.a: linked_list_library.o linked_list_operations.c linked_list_operations.h
# 	ar rcs linked_list_library.a linked_list_library.o

# # Compile the main program
# linked_list.o : linked_list.c linked_list_operations.h linked_list_operations.c
# 	gcc -c linked_list.c -o linked_list.o

# # Link the compiled main program to the static library
# linked_list: linked_list.o linked_list_library.a
# 	gcc -o linked_list linked_list.o -L. linked_list_library.a

# clean:
# 		-rm linked_list *.o *.a
