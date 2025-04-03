#include <stdio.h>

int main() {
    FILE *fptr = fopen("test_file_4.txt", "r");
    if (!fptr)
        printf("Error!");

    char str[100];
    
    fscanf(fptr, "%s", str);

    printf("%s", str);
    fclose(fptr);

    return 0;
}