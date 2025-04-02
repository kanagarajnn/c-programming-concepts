#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int a = 2, b = 3;

    // first way
    int (*ptr1)(int, int) = &add;
    int result = (*ptr1)(a, b);
    printf("%d + %d = %d\n", a, b, result);

    // Second way - more easy
    int (*ptr2)(int, int) = add;
    result = ptr2(a, b);
    printf("%d + %d = %d\n", a, b, result);
}

/*


int *a[10];
- This is not a pointer to array.
- This is an array of 10 pointers as [] has more precedence

int (*a)[10];
- This is a pointer to any array of 10 elements. 

*/