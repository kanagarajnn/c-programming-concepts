#include <stdio.h>

int main() {
    int a[][3] = {1, 2, 3, 4, 5, 6};  // a[2][3] -> a is a ptr to first 1D array

    // {1, 2, 3}
    // {4, 5, 6}

    int(*ptr)[3] = a;

    printf("%d %d ", (*ptr)[1], (*ptr)[2]);  // 2, 3
    ++ptr;
    printf("%d %d ", (*ptr)[1], (*ptr)[2]);  // 5, 6

    return 0;
}