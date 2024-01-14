#include<stdio.h>
//Exercise 4, create a program that crashes by trying to modify read only memory​
int main(){
  char *s_ptr = "Hello world!";
  *s_ptr = "Hi";
  return 0;
}

