#include <stdio.h>

enum Bool {
    False,  // 0
    True    // 1
};

int main() {
    enum Bool var;
    var = True;
    printf("%d", var);
    return 0;
}