#include <stdio.h>
#include <stdlib.h>

int global_var = 10;         // Initialized global (goes to Data Segment - Read/Write)
const int const_var = 100;   // Read-only global (Data Segment - Read Only)
int uninit_global;           // Uninitialized global (BSS Segment)

void my_function() {
    int local_var = 5;       // Local variable (Stack)
    int *ptr = malloc(20);   // Memory from Heap
    printf("local_var = %d\n", local_var);
    free(ptr);
}

int main() {
    static int static_var = 50;  // Initialized static (Data Segment - Read/Write)
    static int static_uninit;    // Uninitialized static (BSS Segment)

    my_function();
    return 0;
}
