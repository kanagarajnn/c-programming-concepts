/*

Fibonacci
n = 6

0, 1, 1, 2, 3, 5

*/

#include <stdio.h>

int main() {
    int a = 0, b = 1, n = 6, result;

    for (int i = 1; i <= n; i++) {
        printf("%d ", a);
        result = a + b;
        a = b;
        b = result;
    }
}