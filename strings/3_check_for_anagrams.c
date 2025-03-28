#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_anagrams(const char *str1, const char *str2) {
    // If lengths differ, they cannot be anagrams
    if (strlen(str1) != strlen(str2)) {
        return false;
    }

    // Initialize count arrays
    int count[256] = {0};

    // Increment count for each character in str1
    // Decrement count for each character in str2
    for (int i = 0; str1[i] && str2[i]; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }

    // If any count is non-zero, strings are not anagrams
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return false;
        }
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
