#include <stdio.h>

int main() {
    FILE *fptr1, *fptr2;
    char filename[100];
    char ch;
    int line, current_line = 1;
    printf("Enter the name of the file: ");
    scanf("%s", filename);

    printf("\n Contents of the file are as follows: \n");
    fptr1 = fopen(filename, "r");

    ch = getc(fptr1);
    while (ch != EOF) {
        printf("%c", ch);
        ch = getc(fptr1);
    }
    rewind(fptr1);

    printf("\n\nEnter the line number you want to delete: ");
    scanf("%d", &line);

    // Opening a duplicate file
    fptr2 = fopen("duplicate.txt", "w");
    ch = getc(fptr1);
    while (ch != EOF) {
        if (ch == '\n')
            current_line++;
        if (current_line != line)
            putc(ch, fptr2);
        ch = getc(fptr1);
    }

    fclose(fptr1);
    fclose(fptr2);

    remove(filename); // delete the file
    rename("duplicate.txt", filename);
    
    return 0;
}