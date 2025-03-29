#include <stdio.h>
#define N 9

int main() {
    int arr[N] = {34, 56, 54, 32, 67, 89, 90, 32, 21};

    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }

    return 0;
}