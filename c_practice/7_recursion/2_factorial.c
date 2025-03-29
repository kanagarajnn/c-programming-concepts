#include <stdio.h>

int fact(int n) {
    if (n <= 1)
        return 1;
    return n * fact(n - 1);
}

int main() {
    int n = 4;
    int factorial = fact(n);
    printf("%d! = %d\n", n, factorial);
}

/*

- fact(4)
- return 4 * fact(3)
- return 3 * fact(2)
- return 2 * fact(1)
- return 1

- fact(4)
- return 24


*/