#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure using a linked list
typedef struct {
    Node* front;  // Points to the front (dequeue from here)
    Node* rear;   // Points to the rear (enqueue here)
} Queue;

// Initialize the queue
void queue_init(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if the queue is empty
bool is_empty(Queue* q) {
    return q->front == NULL;
}

// Enqueue (insert at the rear)
void enqueue(Queue* q, int item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return;
    }
    new_node->data = item;
    new_node->next = NULL;

    if (q->rear == NULL) { // Queue is empty
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    printf("Enqueued: %d\n", item);
}

// Dequeue (remove from the front)
int dequeue(Queue* q, bool* success) {
    if (is_empty(q)) {
        printf("Queue is Empty\n");
        if (success) 
            *success = false;
        return -1;
    }

    Node* temp = q->front;
    int item = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) { // Queue becomes empty
        q->rear = NULL;
    }

    free(temp);
    if (success)
        *success = true;
    
    return item;
}

// Print queue contents
void print_queue(Queue* q) {
    Node* temp = q->front;
    printf("Queue contents: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Free all memory allocated for the queue
void queue_destroy(Queue* q) {
    while (!is_empty(q)) {
        bool success;
        dequeue(q, &success);
    }
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

    queue_destroy(&q);  // Free dynamically allocated memory
    return 0;
}
