/*

Add without +

x++, y--;

stop when y = 0

Handle both when y is positive and negative.

*/

#include <stdio.h>

int main() {
    int a = -3, b = -4;
    int x = a;
    int y = b;

    if (y > 0) {
        while (y != 0) {
            x++;
            y--;
        }
    } else if (y < 0) {
        while (y != 0) {
            x--;
            y++;
        }
    }


    printf("%d + %d = %d", a, b, x);
}