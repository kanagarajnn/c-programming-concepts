#include <stdio.h>

int main() {
    char *a[] = {"2 Oranges", "2 Apples"};
    
    printf("%s\n", a[0]);   // Output: 2 Oranges
    printf("%s\n", a[1]);   // Output: 2 Apples

    // Second Approach
    char data[][10] = {"2 Oranges", "2 Apples"};
    char (*b)[10] = data;

    printf("%s\n", b[0]);   // Output: 2 Oranges
    printf("%s\n", b[1]);   // Output: 2 Apples

    return 0;
}