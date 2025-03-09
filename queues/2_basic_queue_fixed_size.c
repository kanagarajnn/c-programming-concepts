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
    return q->tail == QUEUE_SIZE;
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
    q->tail++;
    
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
    q->head++;
    if (success)
        *success = true;
    
    return item;
}


void print_queue(Queue *q) {
    printf("Queue contents: ");
    for (int i = q->head; i < q->tail; i++) {
        printf("%d ", q->buffer[i]);
    }
    printf("\n");
}


int main() {
    Queue q;
    queue_init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    print_queue(&q);

    bool success;
    int x = dequeue(&q, &success);
    if (success)
        printf("Dequeued: %d\n", x);

    int y = dequeue(&q, &success);
    if (success)
        printf("Dequeued: %d\n", y);

    print_queue(&q);

    return 0;
}



