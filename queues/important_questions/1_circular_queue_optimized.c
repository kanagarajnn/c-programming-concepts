#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdalign.h>
#include <time.h>

#define QUEUE_MAX_SIZE 4  // Must be a power of 2 for efficiency
#define QUEUE_MASK (QUEUE_MAX_SIZE - 1)  // Mask for wrap-around

typedef struct {
    alignas(64) atomic_uint head;  // Read index
    alignas(64) atomic_uint tail;  // Write index
    alignas(64) atomic_uint size;  // Fast lookup for size
    alignas(64) int buffer[QUEUE_MAX_SIZE];  // Data buffer
} CircularQueue;

// Initialize queue
static inline void init_queue(CircularQueue *q) {
    atomic_store(&q->head, 0);
    atomic_store(&q->tail, 0);
    atomic_store(&q->size, 0);
}

// Check if queue is full
static inline bool is_full(CircularQueue *q) {
    return atomic_load(&q->size) == QUEUE_MAX_SIZE;
}

// Check if queue is empty
static inline bool is_empty(CircularQueue *q) {
    return atomic_load(&q->size) == 0;
}

// Non-blocking Enqueue
static inline bool enqueue_nonblocking(CircularQueue *q, int item) {
    uint32_t size = atomic_load(&q->size);
    if (size == QUEUE_MAX_SIZE) {
        return false;  // Queue is full, non-blocking
    }

    uint32_t tail = atomic_load(&q->tail);
    q->buffer[tail & QUEUE_MASK] = item;
    atomic_store(&q->tail, (tail + 1) & QUEUE_MASK);
    atomic_fetch_add(&q->size, 1);

    return true;
}

// Enqueue item with optional overwrite
static inline void enqueue(CircularQueue *q, int item, bool overwrite) {
    if (is_full(q)) {
        if (!overwrite) {
            printf("Queue is Full\n");
            return;
        }
        // Overwrite oldest data
        uint32_t head = atomic_load(&q->head);
        atomic_store(&q->head, (head + 1) & QUEUE_MASK);
        atomic_fetch_sub(&q->size, 1);
    }

    // Insert item
    uint32_t tail = atomic_load(&q->tail);
    q->buffer[tail & QUEUE_MASK] = item;
    atomic_store(&q->tail, (tail + 1) & QUEUE_MASK);
    atomic_fetch_add(&q->size, 1);

    printf("Enqueued %d to queue.\n", item);
}

// Dequeue item
static inline int dequeue(CircularQueue *q) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    uint32_t head = atomic_load(&q->head);
    int item = q->buffer[head & QUEUE_MASK];
    atomic_store(&q->head, (head + 1) & QUEUE_MASK);
    atomic_fetch_sub(&q->size, 1);

    return item;
}

// Print queue contents
static void print_queue(CircularQueue *q) {
    uint32_t i = atomic_load(&q->head);
    uint32_t queue_size = atomic_load(&q->size);

    printf("Queue contents: ");
    for (uint32_t count = 0; count < queue_size; count++) {
        printf("%d ", q->buffer[i & QUEUE_MASK]);
        i = (i + 1) & QUEUE_MASK;
    }
    printf("\n");
}

// Benchmark test for performance
void benchmark() {
    CircularQueue q;
    init_queue(&q);

    const int test_count = 1000000;
    clock_t start = clock();
    
    for (int i = 0; i < test_count; i++) {
        enqueue(&q, i, true);  // Overwrite enabled
        dequeue(&q);
    }
    
    clock_t end = clock();
    printf("Time taken for %d enqueue-dequeue operations: %lf seconds\n",
           test_count, (double)(end - start) / CLOCKS_PER_SEC);
}

// Test cases
void test_queue() {
    CircularQueue q;
    init_queue(&q);

    enqueue(&q, 10, false);
    print_queue(&q);
    enqueue(&q, 20, false);
    print_queue(&q);
    enqueue(&q, 30, false);
    print_queue(&q);
    enqueue(&q, 40, false);  // Queue full now
    print_queue(&q);

    printf("Dequeue: %d\n", dequeue(&q));
    print_queue(&q);

    enqueue(&q, 50, false);
    print_queue(&q);

    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q)); // Queue empty

    // Test overwrite
    enqueue(&q, 33, true);
    enqueue(&q, 60, true);
    enqueue(&q, 70, true);
    enqueue(&q, 80, true);
    enqueue(&q, 90, true);  // Overwrites the oldest element
    print_queue(&q);
}

int main() {
    test_queue();
    // benchmark();
    return 0;
}
