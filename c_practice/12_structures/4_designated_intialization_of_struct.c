#include <stdio.h>

typedef struct employee{
    char *name;
    int age;
    int salary;
} employee;


int main() {
    employee emp1 = {"X", 35, 200000};
    employee emp2 = {.age = 30, .salary = 200000, .name = "Y"};  // Designated Initializer (order does not matter)

    printf("Employee 1 details: %s, %d, %d\n", emp1.name, emp1.age, emp1.salary);
    printf("Employee 2 details: %s, %d, %d\n", emp2.name, emp2.age, emp2.salary);
    
    return 0;
}