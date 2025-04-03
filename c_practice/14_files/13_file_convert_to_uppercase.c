#include <stdio.h>

int main() {
    FILE *fptr1 = fopen("input.txt", "r");
    FILE *fptr2 = fopen("duplicate.txt", "w");

    char c = getc(fptr1);

    while (c != EOF) {
        if (c >= 97 && c <= 122) {
            c = c - 32;
            putc(c, fptr2);
        } else
            putc(c, fptr2);
        c = getc(fptr1);
    }

    fclose(fptr1);
    fclose(fptr2);

    remove("input.txt");
    rename("duplicate.txt", "input.txt");

    return 0;
}