/*

Palindrome:
12321 is palindrome. Reverse and check

*/

#include<stdio.h>

int main() {
    int n = 123212;
    int reverse = 0;
    int remainder = 0;

    int q = n;

    while(q != 0) {
        remainder = q % 10;
        reverse = reverse * 10 + remainder;
        q = q / 10;
    }

    if (reverse == n) {
        printf("Palindrome.\n");
    } else {
        printf("Not a Palindrome\n");
    }

    return 0;
}