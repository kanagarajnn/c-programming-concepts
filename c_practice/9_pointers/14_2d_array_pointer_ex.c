#include <stdio.h>

int main() {
    int arr[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    printf(" arr : %p\n*arr : %p\n", arr, *arr);
    printf(" arr + 1: %p\n*(arr + 1) : %p\n", arr + 1, *(arr + 1));
    printf(" arr + 1: %p\n*arr + 1 : %p\n", arr + 1, *arr + 1);

    int a[][3] = {1, 2, 3, 4, 5, 6};
    int (*ptr1)[3] = a; // ptr1 is a pointer to an array of 3 integers. a[0]

    printf("\n%d %d\n", (*ptr1)[1], (*ptr1)[2]);
    // *ptr1 points to a[0], which is {1, 2, 3}
    // (*ptr)[1] -> a[0][1] -> 2
    // (*ptr)[1] -> a[0][2] -> 3

    return 0;
}