/*

n = 3

  *
 * *
* * *


  12345
1   *
2  * *
3 * * *

rows: n
cols: 2n - 1

n - (i - 1) to n + (i - 1)


*/

#include <stdio.h>

int main() {
    int n;
    printf("How many rows you want in the pyramid?\n");
    scanf("%d", &n);
    printf("%d\n", n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= (2*n - 1); j++) {
            if (j >= n - (i - 1) && j <= n + (i - 1)) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}