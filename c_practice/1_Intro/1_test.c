#include <stdio.h>
#include <limits.h>

int main() {
    printf("Hello World!\n");

    { 
        // Integers
        int a = 23;
        int x, y, z;
        x = y = z = 4;
        printf("%d, %d, %d\n", x, y, z);

        printf("%lu\n", sizeof(long int));

        int var1 = INT_MIN;
        int var2 = INT_MAX;
        printf("Range of signed integer is from: %d to %d\n", var1, var2);

        unsigned int var3 = 0;
        unsigned int var4 = UINT_MAX;
        printf("Range of unsigned integer is from: %u to %u\n", var3, var4);

        short int var5 = SHRT_MIN;
        short int var6 = SHRT_MAX;
        printf("Range of short signed integer is from: %d to %d\n", var5, var6);

        short unsigned int var7 = 0;
        short unsigned int var8 = USHRT_MAX;
        printf("Range of short unsigned integer is from: %u to %u\n", var7, var8);

        long int var9 = LONG_MIN;
        long int var10 = LONG_MAX;
        printf("Range of long signed integer is from: %ld to %ld\n", var9, var10);

        long unsigned int var11 = 0;
        long unsigned int var12 = ULONG_MAX;
        printf("Range of short signed integer is from: %lu to %lu\n", var11, var12);

        printf("sizeof(short) is %lu\n", sizeof(short int));
        printf("sizeof(int) is %lu\n", sizeof(int));
        printf("sizeof(long) is %lu\n", sizeof(long));
        printf("sizeof(long long) is %lu\n\n", sizeof(long long));
    }

    {
        // ============
        // Characters
        // char -> 1 byte
        char var1 = 97;
        printf("%d\n", var1);

        short int var2 = 97;
        printf("%c\n", var2);
    }


    {
        // ============
        // Float & Double & Long Double
        // Float -> 4 bytes
        // Double -> 8 bytes
        // long double -> 12 bytes
        float var1 = 3.141592323232323232; // Precision of 7 digits
        double var2 = 3.141592323232323232; // Precision of 16 digits
        long double var3 = 3.14159232323232323223232; // Precision of 19 digits

        int var4 = 4 / 9;
        printf("4/9 is %d\n", var4);
        
        float var5 = 4 / 9;
        printf("4/9 is %.2f\n", var5);
        
        double var6 = 4.0 / 9.0; // double by default
        printf("4/9 is %.2lf\n", var6);
        
        float var7 = 4.0f / 9.0f; // float as f is added
        printf("4/9 is %.2f\n", var7);
    }

    return 0;
}