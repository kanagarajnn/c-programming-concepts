#include <stdio.h>
#include <stdint.h>

#define POOL_SIZE 32  // Pool size (max 32 due to single uint32_t bitmap)

// Resource Pool Structure
typedef struct {
    int resources[POOL_SIZE];  // Statically allocated integer pool
    uint32_t bitmap;           // 32-bit bitmap for tracking free slots (0 = free, 1 = allocated)
} ResourcePool;

// Initialize the pool
void init_pool(ResourcePool* pool) {
    pool->bitmap = 0;  // All slots start as free (0)
}

// Find first free bit (naive approach for fallback)
int find_first_free_bit(uint32_t bitmap) {
    for (int i = 0; i < POOL_SIZE; i++) {
        if ((bitmap & (1U << i)) == 0) {  // If bit is 0 (free)
            return i;
        }
    }
    return -1;  // No free slots available
}

// Allocate an integer (with first allocation fix)
int* allocate(ResourcePool* pool) {
    if (pool->bitmap == 0xFFFFFFFF) {  // All slots are full
        return NULL;
    }

    // int index = find_first_free_bit(pool->bitmap); O(N) - for loop
    int index = __builtin_ctz(~pool->bitmap);  // Always finds first free bit in O(1)

    pool->bitmap |= (1U << index);  // Mark slot as allocated
    return &pool->resources[index];  // Return pointer to allocated integer
}

// Free an integer
void free_resource(ResourcePool* pool, int* resource) {
    int index = resource - pool->resources;  // Get index using pointer subtraction
    pool->bitmap &= ~(1U << index);  // Mark slot as free by clearing bit
}

// Test function
int main() {
    ResourcePool pool;
    init_pool(&pool);

    // Allocate first integer and store a value
    int* res1 = allocate(&pool);
    if (res1) 
        *res1 = 42;

    // Allocate second integer and store another value
    int* res2 = allocate(&pool);
    if (res2) 
        *res2 = 99;

    // Print allocated values
    printf("Allocated Resource 1: %p, Value: %d\n", res1, res1 ? *res1 : -1);
    printf("Allocated Resource 2: %p, Value: %d\n", res2, res2 ? *res2 : -1);

    // Free the first integer
    free_resource(&pool, res1);
    printf("Freed Resource 1\n");

    // Allocate a new integer (should reuse freed slot)
    int* res3 = allocate(&pool);
    if (res3) 
        *res3 = 77;

    // Print values again
    printf("Reallocated Resource 3: %p, Value: %d\n", res3, res3 ? *res3 : -1);

    return 0;
}
