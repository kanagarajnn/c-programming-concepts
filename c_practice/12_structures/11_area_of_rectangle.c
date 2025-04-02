#include <stdio.h>

typedef struct Point {
    int x;
    int y;
}point;

typedef struct Rectangle {
    point upper_left;
    point lower_right;
}rectangle;

int area(rectangle r) {
    int length, breadth;
    length = r.lower_right.x - r.upper_left.x;
    breadth = r.upper_left.y - r.lower_right.y;

    return length * breadth;
}

int main() {
    rectangle r;
    r.upper_left.x = 3;
    r.upper_left.y = 8;

    r.lower_right.x = 14;
    r.lower_right.y = 2;

    printf("Area of rectangle is %d\n", area(r));
    return 0;
}