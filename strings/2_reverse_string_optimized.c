#include <stdio.h>
#include <string.h>

// Optimized function using pointers
void reverse_string(char *str) {
    if (!str || !*str) return; // Handle NULL and empty strings

    char *left = str;
    char *right = str + strlen(str) - 1;

    while (left < right) {
        // Swap characters using XOR (avoids temporary variable usage)
        *left ^= *right;
        *right ^= *left;
        *left ^= *right;

        left++;
        right--;
    }
}

int main() {
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);
    reverse_string(str);
    printf("Reversed string: %s\n", str);
    return 0;
}
