#include<stdio.h>

void find_two_missing_numbers(int arr[], int n) {
    int xor_all = 0, xor_set = 0, xor_unset = 0;

    // Step 1: XOR all elements in the given array and numbers from 1 to n
    for (int i = 0; i < n - 2; i++)
        xor_all ^= arr[i];
    for (int i = 1; i <= n; i++)
        xor_all ^= i;
    
    // XOR of all array elements and numbers from 1 to N gives xor_all = missing1 ^ missing2.
    // Since all duplicate numbers cancel out (x ^ x = 0), only the missing numbers remain.

    // Step 2: Find rightmost set bit (differs between missing numbers)
    int set_bit = xor_all & -xor_all;

    // Step 3: Split numbers into two groups and XOR separately
    for (int i = 0; i < n - 2; i++) {
        if (arr[i] & set_bit)
            xor_set ^= arr[i];  // Group 1: Numbers with rightmost set bit = 1
        else
            xor_unset ^= arr[i]; // Group 2: Numbers with rightmost set bit = 0
    }

    for (int i = 1; i <= n; i++) {
        if (i & set_bit)
            xor_set ^= i;  // XOR all numbers in Group 1
        else
            xor_unset ^= i; // XOR all numbers in Group 2
    }

    printf("Missing numbers: %d, %d\n", xor_set, xor_unset);
}


int main() {
    int arr[] = {1, 3, 5, 6}; // Missing numbers are 2 and 4
    int n = 6;

    find_two_missing_numbers(arr, n);
    return 0;
}