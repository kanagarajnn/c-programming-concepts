#include <stdio.h>

void count(int n) {
    static int d = 1;
    printf("%d ", n);
    printf("%d ", d);
    d++;

    if (n > 1)
        count(n - 1);
    printf("%d ", d);
}

int main() {
    count(3);
}

/*

Expected output: 3 1 2 2 1 3 4 4 4 
d is a static variable and 
it's value will be retained across function calls (even for recursive functions)

*/