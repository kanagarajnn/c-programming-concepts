#include <stdio.h>
#include <pthread.h>    // pthreads library

int shared_var = 5;     // Shared between threads

void * thread_function(void *arg) {
    shared_var = 10; // Modifying shared variable;
    printf("Thread: shared_var = %d\n", shared_var);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);

    pthread_join(thread, NULL);  // Wait for thread to finish
    printf("Main Thread: shared_var = %d\n", shared_var);

    return 0;
}
