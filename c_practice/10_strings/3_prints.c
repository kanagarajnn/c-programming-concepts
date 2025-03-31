#include<stdio.h>

int main() {
    printf("%c", '\n'); // will work
        printf("%c", "\n"); // string literal and won't work
    putchar('\n'); // will work
        putchar("\n"); // won't work as this is not a char
        puts('\n'); // won't work
    puts("\n"); // will work
        printf("%s", '\n'); // won't work
    printf("%s", "\n"); // will work
}