#include <stdio.h>

int main() {
    FILE *fptr = fopen("test_file_3.txt", "r");
    if (!fptr)
        printf("Error!");

    char str[100];
    fgets(str, 10, fptr); // Reading only 9 characters

    printf("%s", str);
    fclose(fptr);

    return 0;
}