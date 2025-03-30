/*

1) A function cannot return more than one variable
2) If we want to return 2 variables, not possible in func.
3) In that case, pass those 2 variables as input parameters and make them pointers
4) Whatever changes happen to those 2 variables, will be reflected back in the original caller


*/

#include <stdio.h>

void find_min_max(int arr[], int length, int *min, int *max) {
    *min = *max = arr[0];

    for (int i = 1; i < length; i++) {
        if (arr[i] < *min)
            *min = arr[i];
        if (arr[i] > *max)
            *max = arr[i];
    }
}

int main() {
    int arr[] = {42, 1, 2, 3, -20, 99, 123, 43};
    int min, max;
    int length = sizeof(arr) / sizeof(arr[0]);
    
    find_min_max(arr, length, &min, &max);

    printf("Min value is %d\nMax value is %d", min, max);
    
    return 0;
}