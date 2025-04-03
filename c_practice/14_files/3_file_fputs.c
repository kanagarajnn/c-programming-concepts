#include <stdio.h>

int main() {
    FILE *fptr = fopen("test_file_3.txt", "w");
    if (!fptr)
        printf("Error!");

    char str[] = "C programming language";

    // for (int i = 0; str[i] != '\0'; i++)
    //     fputc(str[i], fptr);
    
    fputs(str, fptr);

    fclose(fptr);

    return 0;
}