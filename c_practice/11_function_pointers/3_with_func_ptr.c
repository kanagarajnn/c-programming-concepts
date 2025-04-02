#include <stdio.h>
#define OPERATIONS 4

float sum(float a, float b) {
    return (a + b);
}

float sub(float a, float b) {
    return (a + b);
}

float mult(float a, float b) {
    return (a + b);
}

float div(float a, float b) {
    return (a + b);
}

/*
Use of function pointers will avoid the switch case.
It can dynamically choose the respective function during runtime

*/

int main() {
    int choice;
    float a, b, result;
    float (*func_ptr[OPERATIONS])(float, float) = {sum, sub, mult, div};

    printf("Enter your choice: 0 for sum, 1 for sub, 2 for mult, 3 for div:\n");
    scanf("%d", &choice);
    printf("Enter the two numbers:\n");
    scanf("%f %f", &a, &b);

    result = func_ptr[choice](a, b); 

    printf("Result is %f\n", result);
    return 0;
}