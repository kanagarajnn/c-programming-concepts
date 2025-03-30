/* Matrix Multiplication

a = {{1, 2, 3},
     {1, 2, 1}}

b = {{1, 2},
     {1, 2},
     {3, 1}}

a x b = {{12, 9}, 
         {6, 7}}

matrix a is       2 x 3
matrix b is       3 x 2
matrix a x b is   2 x 2

*/

#include <stdio.h>
#define ROWS_A 2
#define COLS_A 3
#define ROWS_B 3
#define COLS_B 2

void print_array(int a[ROWS_A][COLS_B]) {
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int a[ROWS_A][COLS_A] = {{1, 2, 3},
                             {1, 2, 1}};

    int b[ROWS_B][COLS_B] = {{1, 2},
                             {1, 2},
                             {3, 1}};

    int c[ROWS_A][COLS_B] = {{0, 0},
                             {0, 0}};    // Initialize with 0s

    if (COLS_A != ROWS_B) {
        printf("Matrix A and B cannot be multiplied.");
        return 0;
    }

    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            for (int k = 0; k < ROWS_B; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    print_array(c);
    return 0;
}