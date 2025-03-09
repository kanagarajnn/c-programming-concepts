#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define QUEUE_SIZE 4

/*

0       1       2       3
        x       x       x

t
        h

*/

typedef struct {
    int buffer[QUEUE_SIZE];
    size_t head;   // Read index (Consumer)
    size_t tail;   // Write index (Producer)
} Queue;


void queue_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
}


bool is_full(Queue *q) {
    // return ((q->tail + 1) % QUEUE_SIZE) == q->head;
    return ((q->tail + 1) & (QUEUE_SIZE - 1)) == q->head;
}


bool is_empty(Queue *q) {
    return q->head == q->tail;
}


size_t queue_size(Queue * q) {
    return (q->tail - q->head) & (QUEUE_SIZE - 1);
}


bool enqueue(Queue *q, int item) {
    if (is_full(q)) {
        printf("Queue is Full\n");
        return false;
    }

    q->buffer[q->tail] = item;
    // q->tail = (q->tail + 1) % QUEUE_SIZE;  // Circular increment
    q->tail = (q->tail + 1) & (QUEUE_SIZE - 1);  // Circular increment
    
    return true;
}

int dequeue(Queue *q, bool *success) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        if (success) 
            *success = false;
        return -1;
    }

    int item = q->buffer[q->head];
    // q->head = (q->head + 1) % QUEUE_SIZE;  // Circular increment
    q->head = (q->head + 1) & (QUEUE_SIZE - 1);  // Circular increment
    
    if (success)
        *success = true;
    
    return item;
}

void dequeue_all(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        return;  // Stop execution immediately
    }

    size_t count = (q->tail - q->head) & (QUEUE_SIZE - 1);  // Number of elements
    for (size_t i = 0; i < count; i++) {
        printf("Dequeued: %d\n", q->buffer[q->head]);
        q->head = (q->head + 1) & (QUEUE_SIZE - 1);  // Circular increment
    }
}

void dequeue_all_mem_copy(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        return;
    }

    size_t count = queue_size(q);
    size_t first_chunk = QUEUE_SIZE - q->head;  // From head to end of buffer
    if (first_chunk > count) first_chunk = count;  // Adjust if queue wraps

    int output[count];  // Buffer to hold dequeued elements

    // Copy first part
    memcpy(output, &q->buffer[q->head], first_chunk * sizeof(int));

    // Copy second part if queue wraps
    if (first_chunk < count) {
        memcpy(output + first_chunk, &q->buffer[0], (count - first_chunk) * sizeof(int));
    }

    // Update head after dequeuing
    q->head = (q->head + count) & (QUEUE_SIZE - 1);

    // Print dequeued elements
    for (size_t i = 0; i < count; i++)
        printf("Dequeued: %d\n", output[i]);
}


/**
 * Dequeues all elements from the queue and returns them in a dynamically allocated array.
 * The caller must free the allocated memory.
 */
int* dequeue_all_mem_copy_and_return(Queue *q, size_t *count) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        *count = 0;
        return NULL;
    }

    *count = queue_size(q);
    int *output = (int*)malloc((*count) * sizeof(int));  // Allocate memory for dequeued elements
    if (!output) {
        printf("Memory allocation failed\n");
        *count = 0;
        return NULL;
    }

    size_t first_chunk = QUEUE_SIZE - q->head;  // From head to end of buffer
    if (first_chunk > *count) first_chunk = *count;  // Adjust if queue wraps

    // Copy first part
    memcpy(output, &q->buffer[q->head], first_chunk * sizeof(int));

    // Copy second part if queue wraps
    if (first_chunk < *count) {
        memcpy(output + first_chunk, &q->buffer[0], (*count - first_chunk) * sizeof(int));
    }

    // Update head after dequeuing
    q->head = (q->head + *count) & (QUEUE_SIZE - 1);

    return output;  // Return pointer to dequeued elements
}


void print_queue(Queue *q) {
    printf("Queue contents: ");
    size_t i = q->head;
    while (i != q->tail) {
        printf("%d ", q->buffer[i]);
        // i = (i + 1) % QUEUE_SIZE;  // Circular increment
        i = (i + 1) & (QUEUE_SIZE - 1);  // Circular increment
        
    }
    printf("\n");
}


int main() {
    Queue q;
    queue_init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);  // Queue is full

    print_queue(&q);

    bool success;
    int x = dequeue(&q, &success);
    if (success)
        printf("Dequeued: %d\n", x);
    print_queue(&q);

    // dequeue_all_mem_copy(&q);
    dequeue_all_mem_copy(&q);
    print_queue(&q);

    enqueue(&q, 50); // Will be Added due to Circular Q Implementation
    print_queue(&q);

    // Test dequeue_all_mem_copy_and_return
    Queue q2;
    queue_init(&q2);

    enqueue(&q2, 10);
    enqueue(&q2, 20);
    enqueue(&q2, 30);
    enqueue(&q2, 40);  // Queue is full

    print_queue(&q2);
    size_t count;
    int *dequeued_items = dequeue_all_mem_copy_and_return(&q2, &count);

    if (dequeued_items) {
        printf("Dequeued %zu items: ", count);
        for (size_t i = 0; i < count; i++)
            printf("%d ", dequeued_items[i]);
        printf("\n");

        free(dequeued_items);  // Free allocated memory
    }
    print_queue(&q2);

    return 0;
}



