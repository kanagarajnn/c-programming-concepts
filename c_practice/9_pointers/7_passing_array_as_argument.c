#include <stdio.h>

// int add(int b[], int length) {  // same as below int b[] => *b
int add(int *b, int length) {
    int sum = 0, *p;
    for (p = b; p <= b + length - 1; p++) {
        sum += *p;
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int length = sizeof(arr) / sizeof(arr[0]);

    printf("Sum of array: %d", add(arr, length));
    return 0;
}