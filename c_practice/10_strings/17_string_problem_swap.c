#include <stdio.h>

void fun1(char *s1, char *s2) {
    char *tmp;
    tmp = s1;
    s1 = s2;
    s2 = tmp;
}
/*
str1 = 1000 => "Hi"
str2 = 2000 => "Bye"

fun1(1000, 2000)
tmp = 1000
s1 = 2000
s2  = 1000

Actual values are not changed. str1 and str2 remain unchanged

*/

void fun2(char **s1, char **s2) {
    char *tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

/*
str1 = 3000 => 1000 => "Hi"
str2 = 4000 => 2000 => "Bye"

fun2(3000, 4000)
tmp = 1000
*s1 = 2000  => This changes the str1
*s2  = 1000 => This changes the str2

So, swap takes place correctly

*/


int main() {
    char *str1 = "Hi", *str2 = "Bye";
    
    fun1(str1, str2);
    printf("%s %s ", str1, str2);  // Hi Bye
    
    fun2(&str1, &str2);
    printf("%s %s", str1, str2); // Hi Bye
    
    return 0;
}