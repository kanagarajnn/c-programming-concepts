#include <stdio.h>

int main() {
    FILE *fptr = fopen("test_file_3.txt", "r");
    if (!fptr)
        printf("Error!");

    char ch;
    while(1) {
        ch = fgetc(fptr);
        if (ch == EOF)
            break;
        printf("%c", ch);
    }
    printf("\n");

    fclose(fptr);

    return 0;
}