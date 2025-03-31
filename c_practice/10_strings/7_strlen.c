#include <stdio.h>
#include <string.h>

int main() {
    char *str1 = "Hello";
    char str2[] = "Hello";
    char str3[100] = "Hello";

    printf("Length of %s: %lu\n", str1, strlen(str1));  // strlen will not count null char at end
    printf("Length of %s: %lu\n", str2, strlen(str2)); // prints 5
    printf("Length of %s: %lu\n", str3, strlen(str3));  // prints only 5
    return 0;
}