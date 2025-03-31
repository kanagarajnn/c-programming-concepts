#include <stdio.h>
#include <string.h>

int main() {
    char *s1 = "abc";
    char *s2 = "abce";

    if (strcmp(s1, s2) < 0)
        printf("s1 is less than s2");
    else if (strcmp(s1, s2) > 0)
        printf("s1 is greater than s2");
    else    // s1 == s2
        printf("s1 is equal to s2");

    return 0;
}
