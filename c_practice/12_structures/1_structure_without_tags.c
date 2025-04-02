#include <stdio.h>

struct {
    char *name;
    int age;
    int salary;
} emp1, emp2;


int manager () {
    struct {
        char *name;
        int age;
        int salary;
    } manager;

    manager.age = 27;

    if (manager.age > 30)
        manager.salary = 65000;
    else
        manager.salary = 55000;
    return manager.salary;
}

int main() {
    printf("Enter the salary of employee 1: ");
    scanf("%d", &emp1.salary);
    printf("Enter the salary of employee 2: ");
    scanf("%d", &emp2.salary);
    printf("Employee 1 salary is: %d\n", emp1.salary);
    printf("Employee 1 salary is: %d\n", emp1.salary);
    printf("Manager's salary is: %d\n", manager());
    return 0;
}