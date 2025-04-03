#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fptr = fopen("input1.txt", "r");
    if (fptr == NULL)
        printf("Error message: %s", strerror(errno));

    fseek(fptr, 0, SEEK_END);
    int n = ftell(fptr);
    printf("size of file contents: %d", n);
    return 0;
}