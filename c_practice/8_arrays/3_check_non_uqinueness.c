/*

input: 67827
check if any of the digits appear more than once. 

# Solution 1: Brute Force (Search each digit)
# Time: O(N^2)
# Space: O(N) for storing each digit in an array

# Solution 2: Using Array as Hash map 
# Time: O(N)
# Space: O(N)

a[10] = {0} // initialize 0 for all elements in array
a[6] = 1
a[7] = 1
a[8] = 1
a[2] = 1
a[7] = (already 1, so) not unique
 
*/


#include <stdio.h>

int main() {
    int n = 67827;
    int seen[10] = {0};

    int digit;
    int q = n;
    while (q != 0) {
        digit = q % 10;
        if (seen[digit] == 1) {
            printf("Digit %d is already present. Repetition found", digit);
            return 0;
        } else {
            seen[digit] = 1;
        }
        q /= 10;
    }

    printf("No Repetition found");
    return 0;
}
