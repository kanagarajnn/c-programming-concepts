/*

371 - order n = 3

3 * 3 * 3 = 27
7 * 7 * 7 = 343
1 * 1 * 1 = 1

Add together: 27 + 343 + 1 = 371

Algo:
1) find num of digits : n
2) take each night and multiply n times
3) Add, then check 

*/

#include <stdio.h>

int main() {
    int num = 371;
    int result = 0;
    int n = 0;  // num of digits

    int m = num;
    while (m != 0) {
        m = m / 10;
        n++;
    }

    int digit = 0;
    m = num;
    while (m != 0) {
        digit = m % 10;
        
        int multiplied_value = 1;
        for (int i = 0; i < n; i++) {
            multiplied_value *= digit;
        }
        
        result += multiplied_value;
        m = m / 10;   
    }

    if (result == num) {
        printf("%d is an Armstrong Number\n", num);
    } else {
        printf("%d is not an Armstrong number\n", num);
    }
}
