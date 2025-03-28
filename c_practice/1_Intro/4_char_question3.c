#include <stdio.h>

int main() {
    // On most systems where char is signed
    char c = 255; // becomes -1

    c = c + 10;   // becomes 9
    
    printf("%d\n", c); // prints 9

    return 0;
}