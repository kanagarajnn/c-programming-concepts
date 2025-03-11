#include <stdio.h>
#include <string.h>

#define POOL_SIZE 32  // Pool capacity

// Define the struct stored in the pool
typedef struct {
    int id;
    char name[32];  // Limited to 32 characters
    float value;
} ResourceData;

typedef struct {
    ResourceData resources[POOL_SIZE];  // Statically allocated memory pool
    int free_list[POOL_SIZE];  // Stores indices of available resources
    int free_count;  // Number of free resources
} ResourcePool;

// Initialize the resource pool
void init_pool(ResourcePool* pool) {
    pool->free_count = POOL_SIZE;
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->free_list[i] = i;  // Store indices of free resources
    }
}

// Allocate a resource
ResourceData* allocate(ResourcePool* pool) {
    if (pool->free_count == 0) {
        return NULL;  // No free resources available
    }
    int index = pool->free_list[--pool->free_count];  // Get a free resource index
    return &pool->resources[index];  // Return struct pointer
}

// Free a resource
void free_resource(ResourcePool* pool, void* resource) {
    ResourceData* base = pool->resources;  // Base address of the array
    ResourceData* res_ptr = (ResourceData*) resource;  // Pointer to the resource being freed
    int index = res_ptr - base;  // Compute index using pointer subtraction

    pool->free_list[pool->free_count++] = index;  // Push index back to free list
}

// Test Function
int main() {
    ResourcePool pool;
    init_pool(&pool);

    // Allocate first struct
    ResourceData* res1 = allocate(&pool);
    if (res1) {
        res1->id = 1;
        strcpy(res1->name, "Sensor A");
        res1->value = 23.5;
    }

    // Allocate second struct
    ResourceData* res2 = allocate(&pool);
    if (res2) {
        res2->id = 2;
        strcpy(res2->name, "Sensor B");
        res2->value = 45.2;
    }

    // Print allocated values
    printf("Allocated Resource 1: %p, ID: %d, Name: %s, Value: %.2f\n", res1, res1->id, res1->name, res1->value);
    printf("Allocated Resource 2: %p, ID: %d, Name: %s, Value: %.2f\n", res2, res2->id, res2->name, res2->value);

    // Free the first struct
    free_resource(&pool, res1);
    printf("Freed Resource 1\n");

    // Allocate a new struct (should reuse the freed slot)
    ResourceData* res3 = allocate(&pool);
    if (res3) {
        res3->id = 3;
        strcpy(res3->name, "Sensor C");
        res3->value = 99.9;
    }

    // Print values again
    printf("Reallocated Resource 3: %p, ID: %d, Name: %s, Value: %.2f\n", res3, res3->id, res3->name, res3->value);

    return 0;
}
