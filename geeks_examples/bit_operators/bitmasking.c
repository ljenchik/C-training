
#include <stdio.h> 
  
int main() 
{ 
    // Setting a bit to 1
    // 13 (=0000000000001101) or 1 << 5 (=0000000000100000) = 0000000000101101 (=45)
    int x = 13; 
    printf("Ans: %d \n", x | (1 << 5)); 


    // 45 (=0000000000101101) and 1 << 5 (=0000000000100000) = 0000000000100000 (=32)
    int y = 45; 
    printf("Ans: %d \n", y & (1 << 5)); 

    // Clearing a bit
    // 13 (=0000000000001101) and (~(0000000000000100) = (0000000000000011)) = 0000000000001001(=9)
    int z = 13; 
    printf("Ans: %d\n", z & ~(1 << 2) ); 

    // Flipping a bit
    // 13 (=0000000000001101) ^ (=0000000000001000) = 0000000000000101 (=5) 
    int a = 13; 
    printf("Ans: %d\n", a ^ (1 << 3) ); 
      
   
    return 0; 
}

// The & (bitwise AND) in C takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1.  
// The | (bitwise OR) in C takes two numbers as operands and does OR on every bit of two numbers. The result of OR is 1 if any of the two bits is 1. 
// The ^ (bitwise XOR) in C takes two numbers as operands and does XOR on every bit of two numbers. The result of XOR is 1 if the two bits are different. 