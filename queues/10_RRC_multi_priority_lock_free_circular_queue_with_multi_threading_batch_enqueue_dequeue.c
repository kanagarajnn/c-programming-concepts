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
#define PRIORITY_LEVELS 4  // Must be power of 2 for bitwise optimization

// Message Types (Example RRC Messages)
typedef enum {
    RRC_CONNECTION_SETUP = 0,  // Very High Priority
    SECURITY_MODE_COMMAND = 1,  // High Priority
    MEASUREMENT_REPORT = 2,  // Medium Priority
    SYSTEM_INFORMATION_UPDATE = 3  // Low Priority
} MessageType;

// Message Structure
typedef struct {
    MessageType type;
    int data;
} RRCMessage;

// Lock-Free Circular Queue Structure
typedef struct {
    RRCMessage* buffer[QUEUE_SIZE];  // Storage array
    _Atomic size_t head;  // Read index (Consumer)
    _Atomic size_t tail;  // Write index (Producer)
} LockFreeCircularQueue;

// Multi-Priority Queue Structure
typedef struct {
    LockFreeCircularQueue queues[PRIORITY_LEVELS];  // Separate queues per priority
} MultiPriorityQueue;

// Initialize the Multi-Priority Queue
void queue_init(MultiPriorityQueue* mpq) {
    for (int i = 0; i < PRIORITY_LEVELS; i++) {
        atomic_store(&mpq->queues[i].head, 0);
        atomic_store(&mpq->queues[i].tail, 0);
    }
}

// Check if a queue is full (Lock-Free)
bool is_full(LockFreeCircularQueue* q) {
    return ((atomic_load(&q->tail) + 1) & (QUEUE_SIZE - 1)) == atomic_load(&q->head);
}

// Check if a queue is empty (Lock-Free)
bool is_empty(LockFreeCircularQueue* q) {
    return atomic_load(&q->head) == atomic_load(&q->tail);
}

// Batch Enqueue (Lock-Free) with Priority
size_t batch_enqueue(MultiPriorityQueue* mpq, RRCMessage** items, size_t count, MessageType priority) {
    if (priority < 0 || priority >= PRIORITY_LEVELS) {
        return 0;  // Invalid priority
    }
    
    LockFreeCircularQueue* q = &mpq->queues[priority];
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
    return added;  // Returns the number of items successfully enqueued
}

// Batch Dequeue (Lock-Free) - Always Process Higher Priority First
size_t batch_dequeue(MultiPriorityQueue* mpq, RRCMessage** batch, size_t max_items) {
    size_t count = 0;

    // Always process higher-priority first
    for (int priority = 0; priority < PRIORITY_LEVELS; priority++) {
        LockFreeCircularQueue* q = &mpq->queues[priority];

        // If a higher-priority queue is NOT empty, dequeue only from that queue.
        if (!is_empty(q)) {
            while (count < max_items && !is_empty(q)) {
                size_t head = atomic_load(&q->head);
                batch[count++] = q->buffer[head];
                atomic_store(&q->head, (head + 1) & (QUEUE_SIZE - 1));
            }
            break; // Stop after processing the highest available priority
        }
    }
    
    return count;  // Returns the number of dequeued items
}

// Destroy Queue (Not needed for Lock-Free but added for completeness)
void queue_destroy(MultiPriorityQueue* mpq) {
    // Nothing to free as we use static buffers
}

MultiPriorityQueue mpq;

// Producer function (Dynamically Assigns Priority)
void* producer(void* arg) {
    int id = *(int*)arg;
    RRCMessage* batch[MAX_BATCH];

    for (int i = 0; i < ITEMS_PER_PRODUCER; i += MAX_BATCH) {
        size_t batch_size = 0;
        for (size_t j = 0; j < MAX_BATCH && i + j < ITEMS_PER_PRODUCER; j++) {
            RRCMessage* msg = (RRCMessage*)malloc(sizeof(RRCMessage));
            msg->data = id * 100 + (i + j);

            // Assign priority dynamically
            msg->type = (i < ITEMS_PER_PRODUCER / 4) ? RRC_CONNECTION_SETUP :
                        (i < ITEMS_PER_PRODUCER / 2) ? SECURITY_MODE_COMMAND :
                        (i < 3 * ITEMS_PER_PRODUCER / 4) ? MEASUREMENT_REPORT :
                        SYSTEM_INFORMATION_UPDATE;

            batch[batch_size++] = msg;
        }

        size_t added = batch_enqueue(&mpq, batch, batch_size, batch[0]->type);
        printf("Producer %d: Enqueued %zu items of priority %d\n", id, added, batch[0]->type);
        usleep(100000);  // Simulate work
    }
    return NULL;
}

// Consumer function (Always Dequeues High-Priority First)
void* consumer(void* arg) {
    RRCMessage* batch[MAX_BATCH];
    while (1) {
        size_t count = batch_dequeue(&mpq, batch, MAX_BATCH);
        if (count == 0) {
            usleep(200000);  // If empty, sleep to prevent CPU spin
            continue;
        }

        printf("Consumer: Dequeued %zu items: ", count);
        for (size_t i = 0; i < count; i++) {
            printf("[Priority %d, Data %d] ", batch[i]->type, batch[i]->data);
            free(batch[i]);
        }
        printf("\n");
        usleep(200000);  // Simulate processing
    }
    return NULL;
}

int main() {
    queue_init(&mpq);

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

    queue_destroy(&mpq);
    return 0;
}
