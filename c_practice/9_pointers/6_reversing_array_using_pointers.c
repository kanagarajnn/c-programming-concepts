#include <stdio.h>

#define N 5

int main() {
    int arr[N], *p;

    printf("Enter %d elements\n", N);
    for (p = arr; p <= arr + N - 1; p++)
        scanf("%d", p);
    
    // Reverse and print
    for (p = arr + N - 1; p >= arr; p--)
        printf("%d ", *p);

    return 0;
}