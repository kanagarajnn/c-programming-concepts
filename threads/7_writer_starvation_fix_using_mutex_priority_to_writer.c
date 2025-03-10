#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_data = 0;
pthread_rwlock_t rwlock;
pthread_mutex_t writer_mutex;  // Mutex to prevent starvation

void* reader(void* arg) {
    while (1) {
        pthread_mutex_lock(&writer_mutex);  // Prevent too many readers
        pthread_rwlock_rdlock(&rwlock);
        pthread_mutex_unlock(&writer_mutex);  // Allow other readers

        printf("Reader %ld: Read shared_data = %d\n", (long)arg, shared_data);
        pthread_rwlock_unlock(&rwlock);
        usleep(100000);  // Simulate frequent readers
    }
    return NULL;
}

void* writer(void* arg) {
    while (1) {
        pthread_mutex_lock(&writer_mutex);  // Block new readers while writer is waiting
        pthread_rwlock_wrlock(&rwlock);
        
        shared_data += 10;
        printf("Writer %ld: Updated shared_data to %d\n", (long)arg, shared_data);
        
        pthread_rwlock_unlock(&rwlock);
        pthread_mutex_unlock(&writer_mutex);  // Allow new readers after writing

        usleep(500000);  // Simulate infrequent writers
    }
    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1;

    pthread_rwlock_init(&rwlock, NULL);
    pthread_mutex_init(&writer_mutex, NULL);  // Initialize writer mutex

    pthread_create(&r1, NULL, reader, (void*)1);
    pthread_create(&r2, NULL, reader, (void*)2);
    pthread_create(&r3, NULL, reader, (void*)3);
    pthread_create(&w1, NULL, writer, (void*)1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);

    pthread_rwlock_destroy(&rwlock);
    pthread_mutex_destroy(&writer_mutex);  // Destroy writer mutex
    return 0;
}
