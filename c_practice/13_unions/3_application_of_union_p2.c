#include <stdio.h>

typedef union {
    int a;
    char b;
    double c;
} data1;  // size is 8 bytes

#pragma pack(1)
typedef struct {
    int a;
    char b;
    double c;  
} data2; // size is 13 bytes (with padding: 16 bytes)


int main() {
    data1 arr[10]; // size = 80 bytes
    arr[0].a = 10;
    arr[1].b = 'a';
    arr[2].c = 10.178;
    printf("size of arr[10] is %lu\n", sizeof(arr));

    data2 arr2[10]; // size = 80 bytes
    arr2[0].a = 10;
    arr2[1].b = 'a';
    arr2[2].c = 10.178;
    printf("size of arr2[10] is %lu\n", sizeof(arr2));
    
    return 0;
}