#include <stdio.h>

/*
x = 1000    => 2000 
y = 2000    => 1000
temp = 1000

*/


void swap(int *x, int *y) {
    static int *temp;
    temp = x;
    x = y;
    y = temp;
}

/*
i =  0 =>  1  => 2  =>  3  => 4  => 5  

a = -3 => -2        =>  1        => 6   swap (no effect)
(1000)

b = -6 => -5        => -2        => 3   swap (no effect)
(2000)

while loop
i = 0 done
i = 1 done
i = 2 done
i = 3 done
i = 4 ----


second time function call
=========================
i =  0 =>  1  => 2  =>  3  => 4  => 5  

a =  6 =>  7        =>  10        => 15   swap (no effect)
(1000)

b =  3 =>  4        =>  7        => 12   swap (no effect)
(2000)

while loop
i = 0 done
i = 1 done
i = 2 done
i = 3 done
i = 4 ----

*/

void print_ab() {
    static int i, a = -3, b = -6;
    i = 0;

    while(i <= 4) {
        if ((i++) % 2 == 1)
            continue;
        a += i;
        b += i;
    }

    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);
}

int main() {
    print_ab();
    print_ab();
}


/*

Answer:
a = 6, b = 3
a = 15, b = 12

*/