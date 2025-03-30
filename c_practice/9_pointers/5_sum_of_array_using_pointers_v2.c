#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);

    int *p = &arr[0];
    int sum = 0;

    for (int i = 0; i < length; i++) {
        sum += *(p + i);
    }

    printf("sum is %d\n", sum);

    // Another way of using pointer
    int *p2;
    sum = 0;

    for (p = arr; p <= arr + 4; p++) {
        sum += *p;
    }
    
    printf("sum is %d", sum);
    return 0;
}