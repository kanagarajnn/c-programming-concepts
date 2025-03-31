#include <stdio.h>
#include <string.h>

int main() {
    char p[20];
    char *s = "string";         // Compiler adds '\0' => string\0
    int length = strlen(s);     // 6
    int i;

    for (i = 0; i < length; i++)
        p[i] = s[length - i];

    printf("%s", p);
}


/*

"String"

length = 6

i = 0
p[0] = s[6] = Null
p[1] = s[5] = g
p[2] = s[4] = n
p[3] = s[3] = i
p[4] = s[2] = r
p[5] = s[1] = t



*/
