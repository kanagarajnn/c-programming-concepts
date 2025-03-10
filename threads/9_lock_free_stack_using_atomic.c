#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

atomic_intptr_t top = 0; // Lock-free stack head

void push(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;

    Node* old_top;
    do {
        old_top = (Node*)atomic_load(&top);  // Read current top
        new_node->next = old_top;
    } while (!atomic_compare_exchange_weak(&top, (intptr_t*)&old_top, (intptr_t)new_node));  // CAS

    printf("Pushed: %d\n", value);
}

int pop() {
    Node* old_top;
    do {
        old_top = (Node*)atomic_load(&top);  // Read current top
        if (old_top == NULL) return -1;  // Stack empty
    } while (!atomic_compare_exchange_weak(&top, (intptr_t*)&old_top, (intptr_t)old_top->next));  // CAS

    int value = old_top->data;
    free(old_top);
    printf("Popped: %d\n", value);
    return value;
}

void* thread_function(void* arg) {
    for (int i = 0; i < 5; i++) push(i);
    for (int i = 0; i < 5; i++) pop();
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_function, NULL);
    pthread_create(&t2, NULL, thread_function, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}