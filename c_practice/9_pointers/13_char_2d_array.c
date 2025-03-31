#include <stdio.h>

/*

a[2][3]

{
    {'a', 'b', 'c'},
    {'d', 'e', 'f'}
}

b[3][2]
{
    {'a', 'd'},
    {'b', 'e'},
    {'c', 'f'}
}

char *p = *b;
*p
*(p + 2)

*/

int main() {
    int i, j;
    char a[2][3] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}};
    char b[3][2];
    char *p = *b;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            *(p + 2 * j + i) = a[i][j];
        }
    }

    // Printing b[3][2]
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            printf("%c ", b[i][j]);
        }
        printf("\n");
    }
}

/*

What is the contents of the array b at the end.

b[3][2]
{
    {'a', 'd'},
    {'b', 'e'},
    {'c', 'f'}
}

*/