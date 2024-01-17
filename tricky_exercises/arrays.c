#include <stdio.h>
// void fun(int arr[], unsigned int n)
// {
//     int i;
//     for (i = 0; i < n; i++)
//         printf("%d\n", arr[i]);
// }
 
// int main()
// {
//     int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
//     unsigned int n = sizeof(arr) / sizeof(arr[0]);
//     printf("n = %d\n", n);
//     fun(arr, n);
//     return 0;
// }

// Output: 
// n = 8
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8

// void fun(int* arr)
// {
//     int i;
//     unsigned int n = sizeof(arr) / sizeof(arr[0]);
//      printf("n = %d \n", n);
//     for (i = 0; i < n; i++)
//         printf("%d  ", arr[i]);
// }
 
// int main()
// {
//     int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
//     fun(arr);
//     return 0;
// }
// Output:
// arrays.c:29:15: note: pointer 'arr' declared here
// void fun(int* arr)

#include <stdio.h>
#include <string.h>

// void fun(char* arr)
// {
// 	int i;
// 	unsigned int n = strlen(arr);
// 	printf("n = %d\n", n);
// 	for (i = 0; i < n; i++)
// 		printf("%c ", arr[i]);
// }

// int main()
// {
// 	char arr[] = "geeksquiz";
// 	fun(arr);
// 	return 0;
// }

// // Output: 
// // n = 9
// // g e e k s q u i z % 

#include <stdio.h>
#include <string.h>
 
void fun(char* arr)
{
    int i;
    unsigned int n = strlen(arr);
    printf("n = %d\n", n);
    for (i = 0; i < n; i++)
        printf("%c  ", arr[i]);
}
 
int main()
{
    char arr[]
        = { 'g', 'e', 'e', 'k', 's', 'q', 'u', 'i', 'z' };
    fun(arr);
    return 0;
}

// Output:
// n = 13
// g  e  e  k  s  q  u  i  z  �  t      % 