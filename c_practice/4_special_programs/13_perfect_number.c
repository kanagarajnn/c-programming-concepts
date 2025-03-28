/*
Perfect number = sum of all positive divisors = number


*/

#include <stdio.h>

int main() {
    int num = 6;

    int i, rem, sum = 0;

    for (int i = 1; i < num; i++) {
        rem = num % i;
        if (rem == 0)
            sum += i;
    }

    if (sum == num)
        printf("%d is a perfect number", num);
    else
        printf("%d is not a perfect number", num);
}