#include <stdio.h>

int main() {
    char c[] = "GATE2011";
    char *p = c;
    printf("%s", p + p[3] - p[1]);

    // p = 1000 (Assume)
    // p[3] = *(c + 3) = 'E' = 69
    // p[1] = *(p + 1) = 'A' = 65
    // p + p[3] - p[1] = 1000 + 69 - 65 = 1000 + 4 = 1004
    // Prints 2011 on screen

    return 0;
}