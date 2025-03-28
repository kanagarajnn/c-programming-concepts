#include <stdio.h>

static int i;
static int i = 27;
static int i;

int main() {
    // static int i;
    printf("%d", i); // i will be 27 (data segment). not i = 0 (bss). Once i is stored in data segment, bss will not take into account
    return 0;
}



