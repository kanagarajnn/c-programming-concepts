/*

1 2 3 4 5 6 7 8 9 10
2 1 4 3 6 5 8 7 10 9

*/

#include <stdio.h>

int main() {
    int n = 10;

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            printf("%d ", i + 1);
        } else {
            printf("%d ", i - 1);
        }
    }
}