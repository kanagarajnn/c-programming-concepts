/*
Strong number:

145 = 1! + 4! + 5! = 1 + 24 + 120 = 145

step1 : find each digit
step2 : calculate factorial
step3 : Sum and compare

*/

#include <stdio.h>

int factorial(int);

int main()
{
    int num = 145;
    int result = 0;

    int q = num;
    int digit = 0;
    int digit_factorial = 1;

    while (q != 0)
    {
        digit = q % 10;
        digit_factorial = factorial(digit);
        result += digit_factorial;
        q = q / 10;
    }

    if (result == num) {
        printf("%d is a strong number.\n", num);
    } else {
        printf("%d is not a strong number.\n", num);
    }
}

int factorial(int n) {
    int fact = 1;
    while (n != 0) {
        fact *= n;
        n--;
    }

    return fact;
}