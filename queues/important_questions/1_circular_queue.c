/*

Implement a circular queue

1.Understand
    - input: 
    - output: circular queue
    - write, right

*/

#include <stdio.h>
#include <stdbool.h>

#define QUEUE_MAX_SIZE 4     // Power of 2

typedef struct {
    int buffer[QUEUE_MAX_SIZE];
    int head;   // Read idx
    int tail;   // Write idx
} CircularQueue;


void init_queue(CircularQueue *q) {
    q->head = 0;
    q->tail = 0;
}

bool is_full(CircularQueue *q) {
    return (((q->tail + 1) & (QUEUE_MAX_SIZE - 1)) == q->head);
}

bool is_empty(CircularQueue *q) {
    return q->head == q->tail;
}


void enqueue(CircularQueue *q, int item) {
    if (is_full(q)) {
        printf("Queue is Full\n");
        return;
    }

    q->buffer[q->tail] = item;
    q->tail = (q->tail + 1) & (QUEUE_MAX_SIZE - 1);

    printf("Added %d to circular queue.\n", item);
}


int dequeue(CircularQueue *q) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    int item = q->buffer[q->head];
    q->head = (q->head + 1) & (QUEUE_MAX_SIZE - 1);
    return item;
}

void print_queue(CircularQueue *q) {
    int i = q->head;

    printf("Queue contents: ");
    while (i != q->tail) {
        printf("%d ", q->buffer[i]);
        i = (i + 1) & (QUEUE_MAX_SIZE - 1);
    }
    printf("\n");
}


int main() {
    CircularQueue q;
    init_queue(&q);

    enqueue(&q, 10);
    print_queue(&q);
    enqueue(&q, 20);
    print_queue(&q);
    enqueue(&q, 30);
    print_queue(&q);
    enqueue(&q, 40);      // Queue is full
    print_queue(&q);
    
    printf("Read: %d\n", dequeue(&q));
    print_queue(&q);
    
    enqueue(&q, 50);
    print_queue(&q);
    
    return 0;
}