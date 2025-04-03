#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fptr = fopen("hello.txt", "r"); // This file does not exist

    if (fptr == NULL) {
        printf("The value of error: %d\n", errno);
        printf("The error message is: %s\n", strerror(errno));
        perror("The error message is");
        exit(EXIT_FAILURE);
    } else {
        fclose(fptr);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}