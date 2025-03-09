#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_SIZE 4

/*

0       1       2       3
                        t
h

*/

typedef struct {
    int buffer[QUEUE_SIZE];
    int head;   // Read index (Consumer)
    int tail;   // Write index (Producer)
} Queue;


void queue_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
}


bool is_full(Queue *q) {
    return ((q->tail + 1) % QUEUE_SIZE) == q->head;
}


bool is_empty(Queue *q) {
    return q->head == q->tail;
}


bool enqueue(Queue *q, int item) {
    if (is_full(q)) {
        printf("Queue is Full\n");
        return false;
    }

    q->buffer[q->tail] = item;
    q->tail = (q->tail + 1) % QUEUE_SIZE;  // Circular increment
    
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
    q->head = (q->head + 1) % QUEUE_SIZE;  // Circular increment
    
    if (success)
        *success = true;
    
    return item;
}


void print_queue(Queue *q) {
    printf("Queue contents: ");
    int i = q->head;
    while (i != q->tail) {
        printf("%d ", q->buffer[i]);
        i = (i + 1) % QUEUE_SIZE;  // Circular increment
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

    int y = dequeue(&q, &success);
    if (success)
        printf("Dequeued: %d\n", y);

    print_queue(&q);

    enqueue(&q, 50); // Will be Added due to Circular Q Implementation
    print_queue(&q);

    return 0;
}



