#include <stdio.h>
#include <stdbool.h>

// Bitwise check for power of 2
bool isPowerOf2(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Naive division-based check for power of 2
bool isPowerOf2_div(int n) {
    if (n <= 0) return false;
    while (n > 1) {
        if (n % 2 != 0) return false;
        n /= 2;
    }
    return true;
}


int main() {
    int testCases[] = {0, 1, 2, 3, 4, 8, 16, 31, 32, 64, 127, 128};
    int n = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < n; i++) {
        printf("%d is %s a power of 2\n", testCases[i], isPowerOf2(testCases[i]) ? "" : "NOT");
        printf("%d is %s a power of 2\n", testCases[i], isPowerOf2_div(testCases[i]) ? "" : "NOT");
    }

    return 0;
}


