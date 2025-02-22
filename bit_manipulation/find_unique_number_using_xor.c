#include <stdio.h>

int find_unique(int arr[], int size) {
    int unique = 0;  // Initialize with 0 (identity value for XOR)
    
    for (int i = 0; i < size; i++) {
        unique ^= arr[i];  // XOR every element
    }

    return unique;
}

int main() {
    int arr[] = {3, 7, 3, 2, 7, 5, 5};  // Unique number is 2
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Unique number: %d\n", find_unique(arr, size));

    return 0;
}
