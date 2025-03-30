/*

1. Read the 2D array (5 x 5 array)
2. Traverse the 2D array and compute row sum and col sum
3. Print

Enter row 1: 8 3 9 0 10
Enter row 2: 3 5 17 1 1
Enter row 3: 2 8 6 23 1
Enter row 4: 15 7 3 2 9 
Enter row 5: 6 14 2 6 0

Row total:      30 27 40 36 28
Column total:   34 37 37 32 21

*/

#include <stdio.h>
#define ROWS 5
#define COLS 5

void print_array(int a[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int a[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        printf("Enter row %d: ", i + 1);
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    print_array(a);
    printf("\n");

    int row_total = 0;
    int col_total = 0;

    printf("Row total: ");
    for (int i = 0; i < ROWS; i++)
    {
        row_total = 0;
        for (int j = 0; j < COLS; j++)
        {
            row_total += a[i][j];
        }
        printf("%d ", row_total);
    }
    printf("\n");

    printf("Column total: ");
    for (int i = 0; i < COLS; i++)
    {
        col_total = 0;
        for (int j = 0; j < ROWS; j++)
        {
            col_total += a[j][i];
        }
        printf("%d ", col_total);
    }
    printf("\n");

    
}
