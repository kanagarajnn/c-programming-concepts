#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 5

#define QUEUE_SIZE 8  // Power of 2 for efficiency

// Circular Queue Structure
typedef struct {
    void* buffer[QUEUE_SIZE];  // Storage array
    size_t head;  // Read index (Consumer)
    size_t tail;  // Write index (Producer)
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} CircularQueue;

// Initialize the Circular Queue
void queue_init(CircularQueue* q) {
    q->head = 0;
    q->tail = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

// Check if queue is full
bool is_full(CircularQueue* q) {
    return ((q->tail + 1) & (QUEUE_SIZE - 1)) == q->head;
}

// Check if queue is empty
bool is_empty(CircularQueue* q) {
    return q->head == q->tail;
}

// Enqueue (Producer)
void enqueue(CircularQueue* q, void* data) {
    pthread_mutex_lock(&q->lock);

    while (is_full(q)) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }

    q->buffer[q->tail] = data;
    q->tail = (q->tail + 1) & (QUEUE_SIZE - 1);  // Optimized circular increment

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}

// Dequeue (Consumer)
void* dequeue(CircularQueue* q) {
    pthread_mutex_lock(&q->lock);

    while (is_empty(q)) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }

    void* data = q->buffer[q->head];
    q->head = (q->head + 1) & (QUEUE_SIZE - 1);  // Optimized circular increment

    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    
    return data;
}

// Destroy Queue
void queue_destroy(CircularQueue* q) {
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
}

CircularQueue q;

// Producer function
void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int* item = (int*)malloc(sizeof(int));
        *item = id * 100 + i;
        printf("Producer %d: Enqueued %d\n", id, *item);
        enqueue(&q, item);
        usleep(100000);  // Simulate work
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int* item = (int*)dequeue(&q);
        printf("Consumer: Dequeued %d\n", *item);
        free(item);
    }
    return NULL;
}

int main() {
    queue_init(&q);

    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int ids[NUM_PRODUCERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    queue_destroy(&q);
    return 0;
}

