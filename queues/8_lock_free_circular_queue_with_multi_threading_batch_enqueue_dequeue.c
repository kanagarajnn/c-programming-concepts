#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 8

#define QUEUE_SIZE 8  // Power of 2 for efficiency
#define MAX_BATCH 4   // Max items per batch enqueue/dequeue

// Lock-Free Circular Queue Structure
typedef struct {
    void* buffer[QUEUE_SIZE];  // Storage array
    _Atomic size_t head;  // Read index (Consumer)
    _Atomic size_t tail;  // Write index (Producer)
} LockFreeCircularQueue;

// Initialize the Lock-Free Circular Queue
void queue_init(LockFreeCircularQueue* q) {
    atomic_store(&q->head, 0);
    atomic_store(&q->tail, 0);
}

// Check if queue is full (Lock-Free)
bool is_full(LockFreeCircularQueue* q) {
    return ((atomic_load(&q->tail) + 1) & (QUEUE_SIZE - 1)) == atomic_load(&q->head);
}

// Check if queue is empty (Lock-Free)
bool is_empty(LockFreeCircularQueue* q) {
    return atomic_load(&q->head) == atomic_load(&q->tail);
}

// Lock-Free Batch Enqueue (Producer)
size_t batch_enqueue(LockFreeCircularQueue* q, void** items, size_t count) {
    size_t added = 0;
    size_t tail, next_tail;

    while (added < count) {
        tail = atomic_load(&q->tail);
        next_tail = (tail + 1) & (QUEUE_SIZE - 1);

        if (next_tail == atomic_load(&q->head)) { // Queue is full
            break;
        }

        q->buffer[tail] = items[added++];
        atomic_store(&q->tail, next_tail);
    }

    return added;  // Returns number of items successfully enqueued
}

// Lock-Free Batch Dequeue (Consumer)
size_t batch_dequeue(LockFreeCircularQueue* q, void** batch, size_t max_items) {
    size_t count = 0;
    size_t head;

    while (count < max_items) {
        head = atomic_load(&q->head);
        
        if (head == atomic_load(&q->tail)) { // Queue is empty
            break;
        }

        batch[count++] = q->buffer[head];
        atomic_store(&q->head, (head + 1) & (QUEUE_SIZE - 1));
    }

    return count;  // Returns number of items successfully dequeued
}

// Destroy Queue (Not needed for Lock-Free but added for completeness)
void queue_destroy(LockFreeCircularQueue* q) {
    // Nothing to free as we use static buffer
}

LockFreeCircularQueue q;

// Producer function (Lock-Free Batch Enqueue)
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

// Consumer function (Lock-Free Batch Dequeue)
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
