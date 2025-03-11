#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("nonexistent.txt", "r");

    if (fp == NULL) {
        printf("Error: File could not be opened!\n");  // This goes to stdout
        fprintf(stderr, "Error: File could not be opened!\n");  // This goes to stderr
    }

    return 0;
}
