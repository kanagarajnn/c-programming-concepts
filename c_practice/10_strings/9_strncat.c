#include <stdio.h>
#include <string.h>

int main() {
    char str1[5], str2[100];

    strcpy(str1, "He");
    strcpy(str2, "llo!");
    strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);

    // sizeof(str1) => 5 (size of whole array)
    // strlen(str1) => 2 (string length stored in array not the full size)
    // -1 => for the null character at end

    printf("%s", str1); // concatinated string.
    return 0;
}