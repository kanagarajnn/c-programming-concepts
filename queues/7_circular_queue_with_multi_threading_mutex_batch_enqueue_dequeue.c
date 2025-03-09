#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>  // For memcpy
#include <unistd.h>

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 8

#define QUEUE_SIZE 8  // Power of 2 for efficiency
#define MAX_BATCH 4   // Max items per batch enqueue/dequeue

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

// Batch Enqueue (Producer)
size_t batch_enqueue(CircularQueue* q, void** items, size_t count) {
    pthread_mutex_lock(&q->lock);

    size_t added = 0;
    while (added < count) {
        while (is_full(q)) {
            pthread_cond_wait(&q->not_full, &q->lock);
        }

        while (!is_full(q) && added < count) {
            q->buffer[q->tail] = items[added++];
            q->tail = (q->tail + 1) & (QUEUE_SIZE - 1);  // Optimized circular increment
        }

        pthread_cond_signal(&q->not_empty);
    }

    pthread_mutex_unlock(&q->lock);
    return added;
}

// Batch Dequeue (Consumer)
size_t batch_dequeue(CircularQueue* q, void** batch, size_t max_items) {
    pthread_mutex_lock(&q->lock);

    while (is_empty(q)) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }

    size_t count = 0;
    while (!is_empty(q) && count < max_items) {
        batch[count++] = q->buffer[q->head];
        q->head = (q->head + 1) & (QUEUE_SIZE - 1);  // Optimized circular increment
    }

    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    
    return count;  // Returns number of items dequeued
}

// Destroy Queue
void queue_destroy(CircularQueue* q) {
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);
}

CircularQueue q;

// Producer function (Batch Enqueue)
void* producer(void* arg) {
    int id = *(int*)arg;
    void* batch[MAX_BATCH];

    for (int i = 0; i < ITEMS_PER_PRODUCER; i += MAX_BATCH) {
        size_t batch_size = 0;

        for (size_t j = 0; j < MAX_BATCH && (i + j) < ITEMS_PER_PRODUCER; j++) {
            int* item = (int*)malloc(sizeof(int));
            *item = id * 100 + (i + j);
            batch[batch_size++] = item;
        }

        size_t added = batch_enqueue(&q, batch, batch_size);
        printf("Producer %d: Enqueued %zu items\n", id, added);
        usleep(100000);  // Simulate work
    }
    return NULL;
}

// Consumer function (Batch Dequeue)
void* consumer(void* arg) {
    void* batch[MAX_BATCH];
    while (1) {
        size_t count = batch_dequeue(&q, batch, MAX_BATCH);
        if (count == 0) {
            usleep(200000);  // Prevent busy-waiting
            continue;
        }

        printf("Consumer: Dequeued %zu items: ", count);
        for (size_t i = 0; i < count; i++) {
            int* item = (int*)batch[i];
            printf("%d ", *item);
            free(item);
        }
        printf("\n");
        usleep(200000);  // Simulate processing
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

    // Let consumers process for a while
    sleep(2);
    
    queue_destroy(&q);
    return 0;
}
