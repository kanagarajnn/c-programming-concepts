#include <stdio.h>


int *find_mid(int a[], int n) {
    return &a[n / 2]; // OK: points to memory in arr[], not local
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int *mid = find_mid(arr, n);
    printf("Mid value is %d", *mid); // Outputs 3
    return 0;
}