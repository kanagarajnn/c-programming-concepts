/*
Constants:
1) #define
2) const keyword

*/

#include <stdio.h>
#define PI 3.14159
#define add(x, y) x+y  // Using macros like functions. It will simply get replaced like other constants

#define greater(x, y)   if (x > y) \
                            printf("%d is greater than %d\n", x, y); \
                        else \
                            printf("%d is lesser than %d\n", x, y);


int main() {
    printf("%.5f\n", PI);
    printf("Addition of two numbers: %d\n", add(4, 3));
    greater(5, 6);

    printf("Result of expression: a * b + c is : %d\n", 5 * add(4, 3));
    // 5 * 7 -> not correct
    // First expansion then evaluation: 5 * 4 + 3 = 20 + 3 = 23

    printf("Date: %s\n", __DATE__);
    printf("Time: %s\n", __TIME__);

    const int var = 67;
    // var = 57; // Error. Read-only var cannot be changed
    printf("Var value is %d\n", var);

    return 0;
}
