#include <stdio.h>

int main () {
    int a = 1;
    int b = 1;
    int c = ++a || b++;  
    int d = b-- && --a;

    printf("%d %d %d %d", d, c, b, a);

    return 0;

}

/*

1 - b) bytes
2 - c)
3 - c)
4 - a)
5 - d)
6 - c) Wrong
7 - d)

0000 1010
1111 0101


*/