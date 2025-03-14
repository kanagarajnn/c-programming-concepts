#include <stdio.h>
#include <limits.h>

#define MAX_KEYS 1000   // Maximum number of unique keys
#define MAX_ENTRIES 50   // Maximum number of timestamp-value pairs per key

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
    KeyTimeSeries key_series[MAX_KEYS]; // Hash map representation
    int count; // Number of keys stored
} TimeSeriesDB;


// Initialize the time-series database
void init_time_series_db(TimeSeriesDB *db) {
    db->count = 0;
}

// Linear Search of Key
int find_key_index(const TimeSeriesDB *db, int key) {
    for (int i = 0; i < db->count; i++) {
        if (db->key_series[i].key == key) {
            return i;  // Directly return the index when found
        }
    }
    return -1;  // Return -1 if key is not found
}

// Insert a key-timestamp-value pair
void set(TimeSeriesDB *db, int key, int timestamp, int value) {
    int idx = find_key_index(db, key);

    if (idx == -1) {    // New key
        idx = db->count++;
        db->key_series[idx].count = 0;  // Initialize to 0
        db->key_series[idx].key = key;
    }

    int entry_idx = db->key_series[idx].count++;
    db->key_series[idx].entries[entry_idx].timestamp = timestamp;
    db->key_series[idx].entries[entry_idx].value = value;
}


// Retrieve the most recent value before or at the given timestamp using linear search
// Assumes the entries are in sorted order
int get(const TimeSeriesDB *db, int key, int timestamp) {
    int idx = find_key_index(db, key);
    if (idx == -1) return -1; // Key not found
    
    const TimestampValue *entries = db->key_series[idx].entries;
    int count = db->key_series[idx].count;
    int best = -1;
    
    for (int i = 0; i < count; i++) {
        if (entries[i].timestamp == timestamp) {
            return entries[i].value; // Exact match found
        } else if (entries[i].timestamp < timestamp) {
            best = i; // Store last valid timestamp-value pair
        }
    }
    
    return (best == -1) ? -1 : entries[best].value;
}


// Print all entries for a given key (Optimized)
void print_all_entries_in_db(const TimeSeriesDB *db) {
    for (int i = 0; i < db->count; i++) {
        const KeyTimeSeries *key_series = &db->key_series[i];        
        printf("Key: %d\n", key_series->key);

        for (int j = 0; j < key_series->count; j++) {
            printf("    Timestamp: %d, Value: %d\n", key_series->entries[j].timestamp, key_series->entries[j].value);
        }
        printf("\n");
    }
}


// Test the implementation
int main() {
    TimeSeriesDB db;
    init_time_series_db(&db);

    // Insert test data
    set(&db, 100, 250, 42);
    set(&db, 100, 254, 65);
    set(&db, 100, 267, 23);
    set(&db, 103, 323, 46);
    
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