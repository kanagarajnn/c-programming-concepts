#include <stdio.h>

int main() {
    FILE *fptr = fopen("test_file_2.txt", "w");
    if (!fptr)
        printf("Error!");

    char str[] = "C programming language";

    for (int i = 0; str[i] != '\0'; i++)
        fputc(str[i], fptr);

    fclose(fptr);

    return 0;
}