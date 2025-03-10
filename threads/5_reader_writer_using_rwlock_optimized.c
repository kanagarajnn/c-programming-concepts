#include <stdio.h>
#include <pthread.h>

int shared_data = 0;    // Shared resource
pthread_rwlock_t rwlock;   // Reader-Writer Lock

void * reader(void *arg) {
    pthread_rwlock_rdlock(&rwlock);   // Acquire read lock
    printf("Reader %ld: Read shared_data = %d\n", (long)arg, shared_data);
    pthread_rwlock_unlock(&rwlock);   // Release read lock
    return NULL;
}

void * writer(void *arg) {
    pthread_rwlock_wrlock(&rwlock);   // Acquire write lock
    shared_data += 10;
    printf("Writer %ld: Updated shared_data = %d\n", (long)arg, shared_data);
    pthread_rwlock_unlock(&rwlock);   // Release write lock
    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    pthread_rwlock_init(&rwlock, NULL);

    pthread_create(&r1, NULL, reader, (void *)1);
    pthread_create(&r2, NULL, reader, (void *)2);
    pthread_create(&r2, NULL, reader, (void *)3);
    pthread_create(&w1, NULL, writer, (void *)1);
    pthread_create(&w2, NULL, writer, (void *)2);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}