#include <stdio.h>

#define POOL_SIZE 32  // Number of available integer slots

typedef struct {
    int resources[POOL_SIZE];  // Statically allocated integer pool
    int free_list[POOL_SIZE];  // Tracks available indices
    int free_count;  // Number of free resources
} ResourcePool;

// Initialize the pool
void init_pool(ResourcePool* pool) {
    pool->free_count = POOL_SIZE;
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->free_list[i] = i;  // Store indices of free resources
    }
}

// Allocate an integer
int* allocate(ResourcePool* pool) {
    if (pool->free_count == 0) {
        return NULL;  // No free slots available
    }
    int index = pool->free_list[--pool->free_count];  // Get a free index
    return &pool->resources[index];  // Return pointer to allocated integer
}

// Free an integer
void free_resource(ResourcePool* pool, int* resource) {
    // int index = ((char*)resource - (char*)pool->resources) / sizeof(int); // Division
    int index = resource - pool->resources;  // Get index using pointer subtraction
    pool->free_list[pool->free_count++] = index;  // Push index back to free list
}

// Test function
int main() {
    ResourcePool pool;
    init_pool(&pool);

    // Allocate first integer and store a value
    int* res1 = allocate(&pool);
    if (res1) {
        *res1 = 42;
    }

    // Allocate second integer and store another value
    int* res2 = allocate(&pool);
    if (res2) {
        *res2 = 99;
    }

    // Print allocated values
    printf("Allocated Resource 1: %p, Value: %d\n", res1, res1 ? *res1 : -1);
    printf("Allocated Resource 2: %p, Value: %d\n", res2, res2 ? *res2 : -1);

    // Free the first integer
    free_resource(&pool, res1);
    printf("Freed Resource 1\n");

    // Allocate a new integer (should reuse freed slot)
    int* res3 = allocate(&pool);
    if (res3) {
        *res3 = 77;
    }

    // Print values again
    printf("Reallocated Resource 3: %p, Value: %d\n", res3, res3 ? *res3 : -1);

    return 0;
}
