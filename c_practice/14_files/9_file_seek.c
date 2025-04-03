#include <stdio.h>

int main() {
    FILE *fptr = fopen("Output.txt", "r");
    char str[100];

    fseek(fptr, -5, SEEK_END);
    fscanf(fptr, "%s", str);
    printf("%s", str);

    return 0;
}