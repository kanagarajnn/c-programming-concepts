#include <stdio.h>

int find_missing_number(int arr[], int n) {
    int xor_arr = 0, xor_full = 0;

    // XOR all elements in the given array
    for (int i = 0; i < n - 1; i++)
        xor_arr ^= arr[i];

    // XOR all numbers from 1 to n
    for (int i = 1; i <= n; i++)
        xor_full ^= i;

    // XOR of the two will give the missing number
    return xor_arr ^ xor_full;
}

int main() {
    int arr[] = {1, 2, 4, 5, 6}; // Missing number is 3
    int n = 6; // Should contain numbers from 1 to 6

    printf("Missing number: %d\n", find_missing_number(arr, n));
    return 0;
}
