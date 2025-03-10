#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for linked list stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Stack structure using a linked list
typedef struct {
    Node* top;  // Points to the top of the stack
} Stack;

// Initialize the stack
void stack_init(Stack* s) {
    s->top = NULL;
}

// Check if the stack is empty
bool is_empty(Stack* s) {
    return s->top == NULL;
}

// Push (insert at the top)
void push(Stack* s, int item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed\n");
        return;
    }
    new_node->data = item;
    new_node->next = s->top;  // New node points to the old top
    s->top = new_node;  // Update top
    printf("Pushed: %d\n", item);
}

// Pop (remove from the top)
int pop(Stack* s, bool* success) {
    if (is_empty(s)) {
        printf("Stack is Empty\n");
        if (success)
            *success = false;
        return -1;
    }

    Node* temp = s->top;
    int item = temp->data;
    s->top = s->top->next;  // Move top to the next node

    free(temp);
    if (success)
        *success = true;
    
    return item;
}

// Print stack contents
void print_stack(Stack* s) {
    Node* temp = s->top;
    printf("Stack contents (top to bottom): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Free all memory allocated for the stack
void stack_destroy(Stack* s) {
    while (!is_empty(s)) {
        bool success;
        pop(s, &success);
    }
}

int main() {
    Stack s;
    stack_init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);

    print_stack(&s);

    bool success;
    int x = pop(&s, &success);
    if (success)
        printf("Popped: %d\n", x);

    int y = pop(&s, &success);
    if (success)
        printf("Popped: %d\n", y);

    print_stack(&s);

    stack_destroy(&s);  // Free dynamically allocated memory
    return 0;
}
