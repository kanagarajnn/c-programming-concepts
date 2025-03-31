#include <stdio.h>
#include <string.h>

int main() {
    char str1[10] = "Hello";
    char str2[10];
    char str3[10];

    printf("%s\n", strcpy(str3, strcpy(str2, str1)));
    printf("%s\n", str2);
    printf("%s", str3);
    
    return 0;
}