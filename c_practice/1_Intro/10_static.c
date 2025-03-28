#include <stdio.h>
// #include "static_func.c"

int increment() {
    // static int count = 0;   // Initialization is done by default. not needed
    static int count;
    count++;
    return count;
}

int main()
{
    int value;
    value = increment();
    value = increment();
    value = increment();

    printf("Counter value: %d", value);
    return 0;
}

// Notes:
// Static variables must be initialized only by constants (not variables or func calls)