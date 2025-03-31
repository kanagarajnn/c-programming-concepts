/*

Write your own input function to read the string from user with following functionalities

1) It must continue to read the string even after seeing white space characters.
2) It must stop reading the string after seeing the newline character
3) It must discard extra characters
4) Add, it must return the number of characters it stores in the character array 

*/

#include <stdio.h>

#define N 100

int input(char *s, int n) {
    int i = 0, ch;

    while ((ch = getchar()) != '\n')
        if (i < n)
            s[i++] = ch;
    s[i] = '\0';

    return i;
}

int main() {
    char str[N];
    int count;

    printf("Enter a string: \n");
    count = input(str, 5);

    printf("%d, %s\n", count, str);

    return 0;
}
