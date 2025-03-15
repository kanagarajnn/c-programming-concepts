#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_KEYS    101   // Maximum number of unique keys
#define MAX_ENTRIES 4     // Must be a power of 2 for bitwise modulus
#define EMPTY_KEY   -1    // Indicates an unused key

// Inline macros for circular index arithmetic (power-of-2 optimization)
#define INCR(idx) (((idx) + 1) & (MAX_ENTRIES - 1))
#define DECR(idx) (((idx) - 1) & (MAX_ENTRIES - 1))

// Structure to hold a timestamp-value pair
typedef struct {
    int timestamp;
    int value;
} TimestampValue;

// Structure to hold all timestamp-value pairs for a key (using a circular buffer)
typedef struct {
    int key;                         // Unique key identifier
    TimestampValue entries[MAX_ENTRIES]; // Circular buffer of time-value pairs
    int head;                        // Points to the oldest element
    int tail;                        // Points to the next free slot
    int count;                       // Number of valid entries in the buffer
} KeyTimeSeries;

// Structure to manage multiple keys with direct-indexed hash mapping
typedef struct {
    KeyTimeSeries key_series[MAX_KEYS];
    int count;  // Number of keys in use
} TimeSeriesDB;

// Initialize the time-series database
void init_time_series_db(TimeSeriesDB *db) {
    db->count = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        db->key_series[i].key = EMPTY_KEY;
    }
}

// Simple hash-map lookup using direct indexing (with range check)
int find_key_index(const TimeSeriesDB *db, int key) {
    if (key < 0 || key >= MAX_KEYS) {
        printf("Fatal Error: key %d out of range!\n", key);
        abort();
    }
    return (db->key_series[key].key == key) ? key : EMPTY_KEY;
}

// Optimized set() function:
// 1. Fast-path: if the new timestamp is greater than the last entry, simply append.
// 2. Otherwise, binary search for the insertion position and shift entries.
void set(TimeSeriesDB *db, int key, int timestamp, int value) {
    if (key < 0 || key >= MAX_KEYS) {
        printf("Error: Invalid key %d\n", key);
        return;
    }
    
    int idx = find_key_index(db, key);
    if (idx == EMPTY_KEY) {
        if (db->count >= MAX_KEYS) {
            printf("Database full, cannot add new key\n");
            return;
        }
        idx = key;  // Use key as the direct index
        db->key_series[idx].key = key;
        db->key_series[idx].count = 0;
        db->key_series[idx].head = 0;
        db->key_series[idx].tail = 0;
        db->count++;
    }
    
    KeyTimeSeries *series = &db->key_series[idx];
    TimestampValue *entries = series->entries;
    int count = series->count;

    // If buffer is full, drop the oldest entry.
    if (count >= MAX_ENTRIES) {
        printf("Dropping oldest entry for key %d, Timestamp: %d, Value: %d\n",
               key, entries[series->head].timestamp, entries[series->head].value);
        series->head = INCR(series->head);
        series->count--;
        count--;
    }
    
    // Fast-path: if buffer is empty or new timestamp >= last timestamp, append directly.
    if (count == 0) {
        entries[series->tail].timestamp = timestamp;
        entries[series->tail].value = value;
        series->tail = INCR(series->tail);
        series->count++;
        return;
    }
    
    int last_idx = (series->tail - 1) & (MAX_ENTRIES - 1);
    if (timestamp >= entries[last_idx].timestamp) {
        // Append if timestamp order is maintained.
        entries[series->tail].timestamp = timestamp;
        entries[series->tail].value = value;
        series->tail = INCR(series->tail);
        series->count++;
        return;
    }
    
    // Otherwise, binary search to find the correct insertion position.
    int left = 0, right = count - 1;
    int insert_logical = count;  // Logical offset from head
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        int mid_idx = (series->head + mid) & (MAX_ENTRIES - 1);
        if (entries[mid_idx].timestamp < timestamp) {
            left = mid + 1;
        } else {
            insert_logical = mid;
            right = mid - 1;
        }
    }
    int insert_idx = (series->head + insert_logical) & (MAX_ENTRIES - 1);
    
    // Shift elements to make room.
    // For small MAX_ENTRIES, a loop is efficient.
    int curr = series->tail;
    while (curr != insert_idx) {
        int prev = (curr - 1) & (MAX_ENTRIES - 1);
        entries[curr] = entries[prev];
        curr = prev;
    }
    
    // Insert the new timestamp-value pair.
    entries[insert_idx].timestamp = timestamp;
    entries[insert_idx].value = value;
    series->tail = INCR(series->tail);
    series->count++;
}

// Optimized get() function using binary search over the circular buffer.
// It returns the value for the largest timestamp that is <= the query timestamp.
int get(const TimeSeriesDB *db, int key, int timestamp) {
    int idx = find_key_index(db, key);
    if (idx == EMPTY_KEY) return -1;  // Key not found
    
    const KeyTimeSeries *series = &db->key_series[idx];
    if (series->count == 0) return -1;
    
    const TimestampValue *entries = series->entries;
    int head = series->head, count = series->count;
    
    // If query is before the oldest timestamp, return -1.
    if (timestamp < entries[head].timestamp) {
        return -1;
    }
    
    int lo = 0, hi = count - 1;
    int closest_idx = -1;
    
    while (lo <= hi) {
        int mid = lo + ((hi - lo) >> 1);
        int mid_idx = (head + mid) & (MAX_ENTRIES - 1);
        if (entries[mid_idx].timestamp == timestamp) {
            return entries[mid_idx].value;
        } else if (entries[mid_idx].timestamp < timestamp) {
            closest_idx = mid_idx;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return (closest_idx == -1) ? -1 : entries[closest_idx].value;
}

// Print all entries for debugging purposes.
void print_all_entries_in_db(const TimeSeriesDB *db) {
    for (int i = 0; i < MAX_KEYS; i++) {
        if (db->key_series[i].key != EMPTY_KEY) {
            const KeyTimeSeries *series = &db->key_series[i];
            printf("Key: %d\n", series->key);
            int j = series->head;
            int count = series->count;
            while (count--) {
                printf("  Timestamp: %d, Value: %d\n",
                       series->entries[j].timestamp, series->entries[j].value);
                j = INCR(j);
            }
        }
    }
}

// Test the implementation.
int main() {
    TimeSeriesDB db;
    init_time_series_db(&db);

    // Insert test data for key 100
    set(&db, 100, 223, 77);
    print_all_entries_in_db(&db);
    set(&db, 100, 267, 23);
    print_all_entries_in_db(&db);
    set(&db, 100, 254, 65);
    print_all_entries_in_db(&db);
    set(&db, 100, 250, 42);
    print_all_entries_in_db(&db);
    set(&db, 100, 300, 99);
    print_all_entries_in_db(&db);

    // Insert test data for key 103
    set(&db, 103, 323, 46);
    print_all_entries_in_db(&db);
    
    // Retrieve values for key 100
    printf("get(100, 250): %d\n", get(&db, 100, 250));  // Expected: 42
    printf("get(100, 255): %d\n", get(&db, 100, 255));  // Expected: 65
    printf("get(100, 123): %d\n", get(&db, 100, 123));  // Expected: -1
    printf("get(100, 266): %d\n", get(&db, 100, 266));  // Expected: 65
    printf("get(100, 268): %d\n", get(&db, 100, 268));  // Expected: 23

    return 0;
}
