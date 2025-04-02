#include <stdio.h>

int main() {
    int a[] = {10, 20, 30};

    printf("%d\n", a[2]);   // prints 30
    printf("%d\n", 2[a]);   // also prints 30!

    return 0;
}
