#include <stdio.h>
#include <stdint.h>

#define POOL_SIZE 128  // Supports up to 128 slots
#define BITMAP_WORD_SIZE 32  // Each uint32_t covers 32 slots
#define BITMAP_WORDS (POOL_SIZE / BITMAP_WORD_SIZE)  // Number of words needed

// Resource Pool Structure
typedef struct {
    int resources[POOL_SIZE];  // Statically allocated integer pool
    uint32_t bitmap[BITMAP_WORDS];  // Multiple 32-bit bitmaps for tracking free slots
} ResourcePool;

// Initialize the pool (all slots start as free)
void init_pool(ResourcePool* pool) {
    for (int i = 0; i < BITMAP_WORDS; i++) {
        pool->bitmap[i] = 0;  // All bits set to 0 (all slots free)
    }
}

// Find first free slot in the multi-word bitmap
int find_first_free_slot(ResourcePool* pool, int* word_index) {
    for (int i = 0; i < BITMAP_WORDS; i++) {
        if (pool->bitmap[i] != 0xFFFFFFFF) {  // If there are free slots
            *word_index = i;
            return __builtin_ctz(~pool->bitmap[i]);  // Find first free bit
        }
    }
    return -1;  // No free slots available
}

// Allocate an integer
int* allocate(ResourcePool* pool) {
    int word_index;
    int bit_index = find_first_free_slot(pool, &word_index);
    if (bit_index == -1) return NULL;  // No free slots

    pool->bitmap[word_index] |= (1U << bit_index);  // Mark slot as allocated
    int index = word_index * BITMAP_WORD_SIZE + bit_index;  // Compute absolute index
    return &pool->resources[index];
}

// Free an integer
void free_resource(ResourcePool* pool, int* resource) {
    int index = resource - pool->resources;  // Compute absolute index
    int word_index = index / BITMAP_WORD_SIZE;
    int bit_index = index % BITMAP_WORD_SIZE;

    pool->bitmap[word_index] &= ~(1U << bit_index);  // Mark slot as free
}

// Test function
int main() {
    ResourcePool pool;
    init_pool(&pool);

    // Allocate some integers
    int* res1 = allocate(&pool);
    int* res2 = allocate(&pool);
    int* res3 = allocate(&pool);

    if (res1) *res1 = 42;
    if (res2) *res2 = 99;
    if (res3) *res3 = 77;

    printf("Allocated Resource 1: %p, Value: %d\n", res1, res1 ? *res1 : -1);
    printf("Allocated Resource 2: %p, Value: %d\n", res2, res2 ? *res2 : -1);
    printf("Allocated Resource 3: %p, Value: %d\n", res3, res3 ? *res3 : -1);

    // Free first slot
    free_resource(&pool, res1);
    printf("Freed Resource 1\n");

    // Allocate another resource (should reuse the freed slot)
    int* res4 = allocate(&pool);
    if (res4) *res4 = 55;

    printf("Reallocated Resource 4: %p, Value: %d\n", res4, res4 ? *res4 : -1);

    return 0;
}
