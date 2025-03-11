#include <stdio.h>
#include <stdlib.h>

int main() {
    void *array[3];

    // Allocate memory with error checking
    array[0] = malloc(sizeof(int));
    if (array[0] == NULL) {
        fprintf(stderr, "Memory allocation failed for array[0]\n");
        exit(1);
    }

    array[1] = malloc(sizeof(double));
    if (array[1] == NULL) {
        fprintf(stderr, "Memory allocation failed for array[1]\n");
        free(array[0]); // Free previously allocated memory before exiting
        exit(1);
    }

    array[2] = malloc(sizeof(char) * 6); // Allocate space for 5 characters + null terminator
    if (array[2] == NULL) {
        fprintf(stderr, "Memory allocation failed for array[2]\n");
        free(array[0]);
        free(array[1]);
        exit(1);
    }

    // Assign values
    *(int *)array[0] = 42;
    *(double *)array[1] = 3.14;
    ((char *)array[2])[0] = 'H';
    ((char *)array[2])[1] = 'E';
    ((char *)array[2])[2] = 'L';
    ((char *)array[2])[3] = 'L';
    ((char *)array[2])[4] = 'O';
    ((char *)array[2])[5] = '\0';  // Proper null termination

    // Print values
    printf("Integer: %d\n", *(int *)array[0]);
    printf("Double: %lf\n", *(double *)array[1]);  
    printf("String: %s\n", (char *)array[2]);

    // Free allocated memory
    free(array[0]);
    free(array[1]);
    free(array[2]);

    return 0;
}
