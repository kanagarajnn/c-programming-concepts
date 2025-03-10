#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_data = 0;
pthread_rwlock_t rwlock;

void* reader(void* arg) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("Reader %ld: Read shared_data = %d\n", (long)arg, shared_data);
        pthread_rwlock_unlock(&rwlock);
        // Remove delay to make readers continuous
    }
    return NULL;
}

void* writer(void* arg) {
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        shared_data += 10;
        printf("Writer %ld: Updated shared_data to %d\n", (long)arg, shared_data);
        pthread_rwlock_unlock(&rwlock);
        usleep(500000);  // Keep some delay, but lower than usual
    }
    return NULL;
}

int main() {
    pthread_t readers[5], writer_thread;

    pthread_rwlock_init(&rwlock, NULL);

    // Create 5 readers to heavily acquire the read lock
    for (long i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }

    // Create one writer
    pthread_create(&writer_thread, NULL, writer, (void*)1);

    // Join all threads (will never actually join in this infinite loop)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
