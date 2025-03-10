#include <stdio.h>
#include <pthread.h>

int counter = 0;    // Shared resource
pthread_mutex_t lock; // Declare a mutex

void * thread_function(void* arg) {
    size_t local_counter = 0;
    for (size_t i = 0; i < 1000000; i++)
    {
        local_counter++;  // Modify local variable (faster)
    }

    pthread_mutex_lock(&lock);  // Lock before modifying counter
    counter += local_counter;  // Lock only once
    pthread_mutex_unlock(&lock);    // Unlock after modification

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL); // Initialize mutex

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock); // Destroy mutex after use

    printf("Final Counter Value: %d\n", counter);
    return 0;
}