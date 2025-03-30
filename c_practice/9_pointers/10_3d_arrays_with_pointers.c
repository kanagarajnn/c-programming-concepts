#include <stdio.h>

#define N 2
#define M 2
#define K 3

int main() {
    int arr[N][M][K] = {
                            {
                                {1, 2, 3},
                                {4, 5, 6}
                            },
                            {
                                {7,  8, 9},
                                {10, 11, 12}
                            } 
                        };

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < K; k++)
                printf("%d ", arr[i][j][k]);
    printf("\n");

    // Another way of printing using single for loop (with POINTERS)
    for (int *p = &arr[0][0][0]; p <= &arr[N - 1][M - 1][K - 1]; p++)
        printf("%d ", *p);
    printf("\n");

    // Another way of printing using single for loop (with POINTERS)
    for (int *p = **arr; p <= &arr[N - 1][M - 1][K - 1]; p++)
        printf("%d ", *p);
    printf("\n");

    // Printing second last element in the array
    printf("%d\n", arr[N - 1][M - 1][K - 2]);
    // printf("%d", *(**arr + N - 1 + M - 1 + K - 2));
    printf("%d", *(*(*(arr + (N - 1)) + M - 1) + K - 2));

    return 0;
}