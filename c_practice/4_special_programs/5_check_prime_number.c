/*
Prime number
- 7 - divisible only by 1 and 7

Steps:
1) Start from 2 and divide the num, if rem is 0, then not a prime, else check
2) Do this till n-1, if no divisor, then it is prime

*/

#include <stdio.h>
#include <math.h>

int main() {
    int n = 23;
    int sqrt_n = ceil(sqrt(n));


    if (n == 1) {
        printf("%d is not a prime number.\n", n);
        return 0;
    }

    if (n == 2) {
        printf("%d is a prime number.\n", n);
        return 0;
    }

    for (int i = 2; i <= sqrt_n; i++) {
        if (n % i == 0) {
            printf("%d is not a prime number.\n", n);
            return 0;
        }
    }

    printf("%d is a prime number.\n", n);
}