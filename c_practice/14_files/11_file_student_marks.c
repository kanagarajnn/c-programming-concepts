#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fptr = fopen("students.txt", "w");

    if (fptr == NULL) {
        printf("Error value is: %d\n", errno);
        printf("The error message is: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int n, marks;
    char name[50];

    printf("Enter the number of students: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the name of student: ");
        scanf("%s", name);

        printf("Enter the marks: ");
        scanf("%d", &marks);

        fprintf(fptr, "Name: %s | Marks: %d\n", name, marks);
    }

    fclose(fptr);
    return 0;
}    