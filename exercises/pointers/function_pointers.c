// Consider a function pointer table with 3 entries. 
// Write a function that return a function pointer according to the index received in the parameters.
#include<stdio.h>
void add(int a, int b) {
  printf("Sum : %d\n", a + b);
}
 
void subtract(int a, int b) {
    printf("Difference : %d\n", a - b);
}
 
void multiply(int a, int b) {
    printf("Product : %d\n", a * b);
}


int main() {
   int x = 50, y = 5;
   int index;
    // array of pointers to function of return type int
    void (*arr[3])(int, int)
        = { &add, &subtract, &multiply};

    // Asking  a user to enter an index
    printf("Enter an index (0 <= index <= 2): \n");
    scanf("%d", &index);

    if (index >= 0 && index <= 2) {
        arr[index](x, y);
    }
    else {
      printf("Enter a correct index \n");
    }
    return 0;
  }

