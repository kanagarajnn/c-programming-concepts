#include <stdio.h>

struct Ournode {
    char x, y, z;
};

int main() {
    
    struct Ournode p = {'1', '0', 'a'+2}; // x = '1', y = '0', z = 'c'
    printf("size of struct: %lu\n", sizeof(p));
    struct Ournode *q = &p;
    printf("%c %c", *((char *)q+1), *((char *)q+2));
    return 0;
}

/*

x = '1',  -> 1000
y = '0',  -> 1001
z = 'c'   -> 1002

q = 1000 (address of the whole structure, not the address of the first element)


*/