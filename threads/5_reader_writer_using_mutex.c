#include <stdio.h>
#include <pthread.h>

int shared_data = 0;    // Shared resource
pthread_mutex_t lock;   // Mutex

void * reader(void *arg) {
    pthread_mutex_lock(&lock);
    printf("Reader %ld: Read shared_data = %d\n", (long)arg, shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void * writer(void *arg) {
    pthread_mutex_lock(&lock);
    shared_data += 10;
    printf("Writer %ld: Updated shared_data = %d\n", (long)arg, shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t r1, r2, w1, w2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&r1, NULL, reader, (void *)1);
    pthread_create(&r2, NULL, reader, (void *)2);
    pthread_create(&w1, NULL, writer, (void *)1);
    pthread_create(&w2, NULL, writer, (void *)2);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}