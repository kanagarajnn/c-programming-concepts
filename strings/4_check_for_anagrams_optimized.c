#include <stdio.h>
#include <stdbool.h>

bool are_anagrams(const char *str1, const char *str2) {
    // Handle NULL inputs
    if (!str1 || !str2) return false;

    // Count character frequency
    int count[256] = {0};

    // Iterate both strings in a single loop
    while (*str1 && *str2) {
        count[(unsigned char)(*str1)]++;
        count[(unsigned char)(*str2)]--;
        str1++;
        str2++;
    }

    // If one string is longer than the other, return false
    if (*str1 || *str2) return false;

    // Check if all counts are zero
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) 
            return false;
    }

    return true;
}

int main() {
    const char *str1 = "listen";
    const char *str2 = "silent";

    if (are_anagrams(str1, str2)) {
        printf("\"%s\" and \"%s\" are anagrams.\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not anagrams.\n", str1, str2);
    }

    return 0;
}
