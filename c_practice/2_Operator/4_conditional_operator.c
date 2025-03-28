#include <stdio.h>

int main() {
    char result;
    int marks = 100;

    result = (marks > 33) ? 'p' : 'f';
    printf("result is %c\n", result);

    int var = 75;
    int var2 = 56;
    int num;

    num = sizeof(var) ? (var2 > 23 ? ((var == 75) ? 'A' : 0) : 0) : 0;

    printf("%d", num); // Prints 65 (= 'A')

    return 0;
}
