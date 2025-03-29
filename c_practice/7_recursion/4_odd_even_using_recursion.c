/*

Using indirect recursion

1 2 3 4 5 6 7 8 9 10
2 1 4 3 6 5 8 7 10 9


*/

#include <stdio.h>
int n = 1;
void odd();
void even();

void odd() {
    if (n <= 10) {
        printf("%d ", n + 1);
        n++;
        even();
    }
    return;
}

void even() {
    if (n <= 10) {
        printf("%d ", n - 1);
        n++;
        odd();
    }
    return;
}

int main() {
    odd();
}