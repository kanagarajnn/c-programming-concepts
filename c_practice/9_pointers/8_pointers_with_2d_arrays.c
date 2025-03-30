/*

C stores 2D arrays as row major order

row1, row2, row3, ...

We can treat it as 1D using pointers

*/


#include <stdio.h>
#define ROWS 2
#define COLS 3

int main() {
    int arr[ROWS][COLS] = {{1, 2, 3},
                           {4, 5, 6}};

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            printf("%d ", arr[i][j]);
    printf("\n");

    // Another way of printing using single for loop (with POINTERS)
    for (int *p = &arr[0][0]; p <= &arr[ROWS - 1][COLS - 1]; p++)
        printf("%d ", *p);

    return 0;
}