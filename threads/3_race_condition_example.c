#include <stdio.h>
#include <pthread.h>

int counter = 0;    // Shared resource

void * thread_function(void* arg) {
    for (size_t i = 0; i < 1000000; i++) {
        counter++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final Counter Value: %d\n", counter);
    return 0;
}