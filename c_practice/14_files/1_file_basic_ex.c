#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("test_file.txt", "w");
    if (!fptr)
        printf("Error!");

    char str[100];
    printf("Enter the string: ");
    scanf("%s", str);

    fprintf(fptr, "%s", str);
    fclose(fptr);

    return 0;
}