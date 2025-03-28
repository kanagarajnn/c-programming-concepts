/*

Ex 1:
====
str1 = "listen"
str2 = "silent"
- This is an Anagram

Ex 1:
====
str1 = "listen"
str2 = "silence"

- This is not an Anagram


Solution 1: Brute Force
=========================
- Number of chars must be same
- Each char of str1 must be present in st2
- For each char in str1
-      Find char in str2 O(M)
- Time: O(N * M)
- Space: O(1)


Solution 2: Use Hash Table
=========================
- Store chars of str2 in a hash table (for simplicity, assume array index based hash)
- For each char in str1
-      Find char in str2 O(1) - constant lookup / search
- Time: O(N + M)
- Space: O(1)



*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// ASCII - 7 bits - 128 chars, 
// 0 to 31 - control chars (NUL, CR, etc)
// 32 to 126 - printable chars (letters, digits, punctuation, symbols)
// 127 - control char (DEL)
// Extended ASCII - 8 bits - 256 chars
#define TOTAL_ASCII_CHARS 255


bool are_anagrams(const char *str1, const char *str2) {
    // If lengths differ, they cannot be anagrams
    if (strlen(str1) != strlen(str2)) {
        return false;
    }

    int count[TOTAL_ASCII_CHARS] = {0};

    for (int i = 0; i < strlen(str2); i++) {
        count[str2[i]]++;
    }

    for (int i = 0; i < strlen(str1); i++) {
        count[str1[i]]--;
    }

    for (int i = 0; i < 255; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}


int main() {
    const char str1[] = "listen"; // string literal
    // const char str1[] = { 'l', 'i', 's', 't', 'e', 'n', '\0' }; // Equivalent to prev line
    printf("size of %s: %zu\n", str1, sizeof(str1)); // prints size as 7 (not 6)


    const char str2[] = "silent";
    printf("size of %s: %zu\n", str2, sizeof(str2)); // prints size as 7 (not 6)

    if (are_anagrams(str1, str2)) {
        printf("\"%s\" and \"%s\" are anagrams.\n", str1, str2);
    } else {
        printf("\"%s\" and \"%s\" are not anagrams.\n", str1, str2);
    }

    return 0;
}

/*

Notes:

1) String literals are always null-terminated by default (size includes null char)
    const char str1[] = "listen"; // string literal
    // const char str1[] = { 'l', 'i', 's', 't', 'e', 'n', '\0' }; // Equivalent to prev line

    const char *str1 = "listen"; // string literal

    printf("size of %s: %zu\n", str1, sizeof(str1)); // prints size as 7 (not 6)


2) Read-only Memory: string literals like "abc" shown below
    char *str = "abc";
    str[0] = 'A'; // ❌ undefined behavior (trying to modify read-only memory)

3) Compare array vs pointer
    const char str1[] = "abc";
        - Creates a copy of the string literal in an array (writable)
        - but const keyword makes it not writable
    const char *str1 = "abc";
        - Points to a string literal in read-only memory (not writable)

    



*/