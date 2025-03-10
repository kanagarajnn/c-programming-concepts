#include <stdio.h>
#include <unistd.h> // fork()

int main() {
    int x = 5;
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        x = 10;
        printf("Child Process: x = %d\n", x);
    } else {
        // Parent process
        sleep(1);   // Ensure child prints first
        printf("Parent Process: x = %d\n", x);
    }

    return 0;
}