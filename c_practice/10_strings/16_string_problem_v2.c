#include <stdio.h>

void foo(char *a) {
    if (*a && *a != ' ') {
        foo(a + 1);
        putchar(*a);
    }
}

/*
foo("A")
foo("B")
foo("C")
foo("D")
foo(" ")

foo("A") -> A
foo("B") -> B
foo("C") -> C
foo("D") -> D

DCBA

*/

int main() {
    foo("ABCD EFGH");
    return 0;
}