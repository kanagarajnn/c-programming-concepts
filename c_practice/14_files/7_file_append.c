#include <stdio.h>

int main() {
    FILE *fptr = fopen("Output.txt", "a+");
    char str[100];
    char *s = " is useful for beginners";
    fputs(s, fptr);
    
    rewind(fptr);
    
    fgets(str, 100, fptr);
    printf("%s", str);
    fclose(fptr);
    
    return 0;
}