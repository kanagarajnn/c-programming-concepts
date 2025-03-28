#include <stdio.h>

int global_var; // declaration and definition
extern int extern_var; // only declaration (defn in some other file)
// save memory and reusable

// Multiple declarations are allowed, not multiple
extern int extern_var; 
extern int extern_var;

extern int extern_var_defined = 99; // Both declaration and definition happens

int main() {
    int var;
    printf("Local auto variable's initial value: %d\n", var); // Junk

    printf("Global variable's initial value: %d\n", global_var); // 0

    static int static_var;
    printf("Local static variable's initial value: %d\n", static_var); // 0
}