#include <stdio.h>
#include <stdint.h>

#define POOL_SIZE 32  // Max 32 due to uint32_t bitmap

// Resource Pool Structure
typedef struct {
    int resources[POOL_SIZE];  // Statically allocated integer pool
    uint32_t bitmap;           // 32-bit bitmap for tracking free slots (0 = free, 1 = allocated)
} ResourcePool;

// Initialize the pool
void init_pool(ResourcePool* pool) {
    pool->bitmap = 0;  // All slots start as free (0)
}

// Find first free bit (naive fallback approach)
int find_first_free_bit(uint32_t bitmap) {
    for (int i = 0; i < POOL_SIZE; i++) {
        if ((bitmap & (1U << i)) == 0) {  // If bit is 0 (free)
            return i;
        }
    }
    return -1;  // No free slots available
}

// Allocate an integer (O(1) using __builtin_ctz)
int* allocate(ResourcePool* pool) {
    if (pool->bitmap == 0xFFFFFFFF) {  // All slots are full
        return NULL;
    }

    int index = __builtin_ctz(~pool->bitmap);  // O(1) find first free bit
    pool->bitmap |= (1U << index);  // Mark slot as allocated
    return &pool->resources[index];  // Return pointer to allocated integer
}

// Bulk allocate function
size_t bulk_allocate(ResourcePool* pool, int** out_resources, size_t count) {
    size_t allocated = 0;
    
    for (size_t i = 0; i < count && pool->bitmap != 0xFFFFFFFF; i++) {
        int index = __builtin_ctz(~pool->bitmap);  // Find free slot in O(1)
        pool->bitmap |= (1U << index);  // Mark as allocated
        out_resources[allocated++] = &pool->resources[index];  // Store pointer
    }

    return allocated;  // Return number of successfully allocated resources
}

// Free an allocated resource
void free_resource(ResourcePool* pool, int* resource) {
    int index = resource - pool->resources;  // Get index using pointer arithmetic
    if (index >= 0 && index < POOL_SIZE) {
        pool->bitmap &= ~(1U << index);  // Mark slot as free
    }
}

// Bulk free function
void bulk_free(ResourcePool* pool, int** resources, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free_resource(pool, resources[i]);
    }
}

// Test function
int main() {
    ResourcePool pool;
    init_pool(&pool);

    // Test Single Allocation
    int* res1 = allocate(&pool);
    int* res2 = allocate(&pool);

    if (res1) *res1 = 42;
    if (res2) *res2 = 99;

    printf("Allocated Resource 1: %p, Value: %d\n", res1, res1 ? *res1 : -1);
    printf("Allocated Resource 2: %p, Value: %d\n", res2, res2 ? *res2 : -1);

    // Bulk Allocation
    int* bulk_resources[5];
    size_t allocated = bulk_allocate(&pool, bulk_resources, 5);
    printf("Bulk Allocated %zu Resources\n", allocated);
    for (size_t i = 0; i < allocated; i++) {
        *bulk_resources[i] = i + 100;
        printf("Bulk Allocated Resource %zu: %p, Value: %d\n", i, bulk_resources[i], *bulk_resources[i]);
    }

    // Free some resources
    free_resource(&pool, res1);
    printf("Freed Resource 1\n");

    // Bulk Free
    bulk_free(&pool, bulk_resources, allocated);
    printf("Bulk Freed %zu Resources\n", allocated);

    // Test reallocation
    int* res3 = allocate(&pool);
    if (res3) *res3 = 77;
    printf("Reallocated Resource 3: %p, Value: %d\n", res3, res3 ? *res3 : -1);

    return 0;
}
