#include <stdio.h>

typedef struct employee{
    char *name;
    int age;
    int salary;
} employee;


int main() {
    employee emp[2] = {{"X", 35, 200000}, {.age = 30, .salary = 200000, .name = "Y"}};

    emp[0] = (employee){"X2", 35, 200000};
    emp[1] = (employee){.age = 30, .salary = 200000, .name = "Y2"};

    for (int i = 0; i < 2; i++) {
        printf("Employee %d details: %s, %d, %d\n", i + 1, emp[i].name, emp[i].age, emp[i].salary);
    }
    
    return 0;
}