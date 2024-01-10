// #include <stdio.h>
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

// #include <stdio.h>
// void fun(int* arr)
// {
//     int i;
//     unsigned int n = sizeof(arr) / sizeof(arr[0]);
//      printf("n = %d \n", n);
//     for (i = 0; i < n; i++)
//         printf("%d  ", arr[i]);
// }
 
// // Driver program
// int main()
// {
//     int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
//     fun(arr);
//     return 0;
// }

#include <stdio.h>
#include <string.h>

void fun(char* arr)
{
	int i;
	unsigned int n = strlen(arr);
	printf("n = %d\n", n);
	for (i = 0; i < n; i++)
		printf("%c ", arr[i]);
}

// Driver program
int main()
{
	char arr[] = "geeksquiz";
	fun(arr);
	return 0;
}
