/*
Power of an integer:
base
exponent

*/

#include<stdio.h>

int main() {
    int base = 2;
    int exponent = -3;
    double power = 1;  // result
    int expo = exponent;

    if (expo > 0) {
        while (expo != 0) {
            power *= base;
            expo--;
        }
    } else {
        while (expo != 0) {
            power *= 1.0 / base;
            expo++;
        }

    }

    printf("%d^%d is %f\n", base, exponent, power);
}