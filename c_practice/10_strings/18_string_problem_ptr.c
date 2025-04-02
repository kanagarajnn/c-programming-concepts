#include <stdio.h>
#include <string.h>

int main() {
    char *c = "GATECSIT2017";
    char *p = c;
    printf("%d", (int)strlen(c + 2[p] - 6[p] - 1));

    /*
    c = 1000
    p = 1000

        c +     2[p] -  6[p] - 1
    = 1000 +  *(2 + p) -  *(6 + p) - 1
    = 1000 +  *(2 + 1000) -  *(6 + 1000) - 1
    = 1000 +  *(1002) -  *(1006) - 1
    = 1000 + 'T' - 'I' - 1
    = 1000 + 84 - 73 - 1
    = 1000 + 84 - 74
    = 1000 + 10
    = 1010

    strlen(1010) => 2



    A = 65
    Z = 90
    T = 84 ==>
    I = 73 ===>


    T U V W X Y Z
    */
    return 0;
}