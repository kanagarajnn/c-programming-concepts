// Direct Indexing Hashmap
// Assumes keys are unique

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define MAX_KEYS 1000   // Maximum number of unique keys
#define MAX_ENTRIES 5   // Maximum number of timestamp-value pairs per key
#define EMPTY_KEY -1    // Key not in use

// Structure to hold a timestamp-value pair
typedef struct {
    int timestamp;  // Timestamp
    int value;      // Associated value
} TimestampValue;

// Structure to hold all time-value pairs for a specific key
typedef struct {
    int key;  // Unique key identifier
    TimestampValue entries[MAX_ENTRIES]; // Array of time-value pairs
    int count; // Number of timestamp-value pairs stored for this key
} KeyTimeSeries;

// Structure to manage multiple keys and their respective time-value mappings
typedef struct {
    KeyTimeSeries key_series[MAX_KEYS]; // Hash Map (Direct Indexing)
    int count; // Number of keys stored
} TimeSeriesDB;


// Initialize the time-series database
void init_time_series_db(TimeSeriesDB *db) {
    db->count = 0;

    for (int i = 0; i < MAX_KEYS; i++) {
        db->key_series[i].key = EMPTY_KEY;
    }
}

// Hash Map Search of Key
int find_key_index(const TimeSeriesDB *db, int key) {
    if (key >= MAX_KEYS) {
        printf("Fatal Error: key is larger than the supported value!\n");
        abort(); // Force crash
    }

    // assert(key < MAX_KEYS);
    return (db->key_series[key].key == key) ? key : EMPTY_KEY;
}


// Insert a key-timestamp-value pair in sorted order
void set(TimeSeriesDB *db, int key, int timestamp, int value) {
    int idx = find_key_index(db, key);

    // If key is not found, insert a new key in the database    
    if (idx == EMPTY_KEY) {
        if (db->count >= MAX_KEYS) {
            printf("Database full, cannot add new key\n");
            return;
        }
        idx = key;      // For hash map
        db->key_series[idx].key = key;
        db->key_series[idx].count = 0;
        db->count++;
    }

    // Reference to the key's entry list
    TimestampValue *entries = db->key_series[idx].entries;
    int count = db->key_series[idx].count;
    
    // Check if space is available for a new entry
    if (count >= MAX_ENTRIES) {
        printf("No space left for key %d\n", key);
        return;
    }

    // Insert the new entry in sorted order (Shift elements to maintain order)
    int insert_pos = count;
    while (insert_pos > 0 && entries[insert_pos - 1].timestamp > timestamp) {
        entries[insert_pos] = entries[insert_pos - 1];  // copy struct directly
        insert_pos--;
    }

    entries[insert_pos].timestamp = timestamp;
    entries[insert_pos].value = value;
    db->key_series[idx].count++;
}

// Binary Search: Retrieve the most recent value before or at the given timestamp
// Assumes the entries are in sorted order
int get(const TimeSeriesDB *db, int key, int timestamp) {
    int idx = find_key_index(db, key);
    if (idx == -1) return -1;   // Key not found

    const TimestampValue *entries = db->key_series[idx].entries;
    int count = db->key_series[idx].count;

    if (count == 0) return -1;  // No entries for the key

    int lo = 0, hi = count - 1, closest_idx = -1;

    while(lo <= hi) {
        // Integer overflow optimization and Bit manipulation for division by 2
        int mid = lo + ((hi - lo) >> 1);
        if (entries[mid].timestamp == timestamp) {
            return entries[mid].value;
        } else if (entries[mid].timestamp < timestamp) {
            closest_idx = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return (closest_idx == -1) ? -1 : entries[closest_idx].value;
}


// Print all entries for a given key (Optimized)
void print_all_entries_in_db(const TimeSeriesDB *db) {
    for (int i = 0; i < MAX_KEYS; i++) {
        if (db->key_series[i].key != -1) {
            const KeyTimeSeries *key_series = &db->key_series[i];        
            printf("Key: %d\n", key_series->key);

            for (int j = 0; j < key_series->count; j++) {
                printf("    Timestamp: %d, Value: %d\n", key_series->entries[j].timestamp, key_series->entries[j].value);
            }
            printf("\n");
        }
    }
}


// Test the implementation
int main() {
    TimeSeriesDB db;
    init_time_series_db(&db);

    // Insert test data
    set(&db, 100, 267, 23);
    set(&db, 100, 254, 65);
    set(&db, 100, 250, 42);
    set(&db, 103, 323, 46);
    // set(&db, 1000, 323, 46); // Key invalid
    
    // Print entries
    print_all_entries_in_db(&db);

    // Retrieve values
    printf("get(100, 250): %d\n", get(&db, 100, 250));  // Expected: 42
    printf("get(100, 255): %d\n", get(&db, 100, 255));  // Expected: 65
    printf("get(100, 123): %d\n", get(&db, 100, 123));  // Expected: -1
    printf("get(100, 266): %d\n", get(&db, 100, 266));  // Expected: 65
    printf("get(100, 268): %d\n", get(&db, 100, 268));  // Expected: 23
    
    return 0;
}