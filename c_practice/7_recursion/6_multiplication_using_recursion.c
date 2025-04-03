#include <stdio.h>

int multiply(int x, int y) {
    if (x == 0)
        return 0;

    return y + multiply(x - 1, y);
}

int main() {
    int x = 2, y = 9;
    printf("%d x %d = %d", x, y, multiply(x, y));
    return 0;
}