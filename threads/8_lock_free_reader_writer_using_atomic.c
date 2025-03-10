#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>  // C11 atomic operations

_Atomic int counter = 0;  // Lock-free counter

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        atomic_fetch_add(&counter, 1);  // Atomically increment counter
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final Counter Value: %d\n", counter);
    return 0;
}
