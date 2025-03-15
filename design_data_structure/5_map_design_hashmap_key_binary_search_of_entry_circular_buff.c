#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define MAX_KEYS 101   // Maximum number of unique keys
#define MAX_ENTRIES 4  // Maximum number of timestamp-value pairs per key (must be a power of 2)
#define EMPTY_KEY -1   // Key not in use

// Structure to hold a timestamp-value pair
typedef struct {
    int timestamp;  // Timestamp
    int value;      // Associated value
} TimestampValue;

// Structure to hold all time-value pairs for a specific key
typedef struct {
    int key;                        // Unique key identifier
    TimestampValue entries[MAX_ENTRIES]; // Array of time-value pairs (circular buffer)
    int head;                       // Pointer to the oldest element
    int tail;                       // Pointer to the next free slot
    int count;                      // Number of entries currently stored
} KeyTimeSeries;

// Structure to manage multiple keys and their respective time-value mappings
typedef struct {
    KeyTimeSeries key_series[MAX_KEYS]; // Direct-indexed hash map of keys
    int count;                          // Number of keys stored
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
    if (key >= MAX_KEYS || key < 0) {
        printf("Fatal Error: key %d is out of supported range!\n", key);
        abort(); // Force crash
    }
    return (db->key_series[key].key == key) ? key : EMPTY_KEY;
}

// Insert a key-timestamp-value pair in sorted order into the circular buffer
void set(TimeSeriesDB *db, int key, int timestamp, int value) {
    if (key >= MAX_KEYS || key < 0) {
        printf("Error: Invalid key %d\n", key);
        return;
    }

    int idx = find_key_index(db, key);
    // If key is not found, create a new entry for this key.
    if (idx == EMPTY_KEY) {
        if (db->count >= MAX_KEYS) {
            printf("Database full, cannot add new key\n");
            return;
        }
        idx = key; // Direct indexing for hash map
        db->key_series[idx].key = key;
        db->key_series[idx].count = 0;
        db->key_series[idx].head = 0;
        db->key_series[idx].tail = 0;
        db->count++;
    }

    KeyTimeSeries *series = &db->key_series[idx];
    TimestampValue *entries = series->entries;
    int count = series->count;

    printf("Key: %d, Count of entries: %d\n", key, count);

    // If the buffer is full, drop the oldest element.
    if (count >= MAX_ENTRIES) {
        printf("Dropping oldest entry for key %d, Timestamp: %d, Value: %d\n",
               key, entries[series->head].timestamp, entries[series->head].value);
        series->head = (series->head + 1) & (MAX_ENTRIES - 1);
        series->count--;
        count--;
    }

    // If there are no entries after a possible drop, simply insert.
    if (count == 0) {
        entries[0].timestamp = timestamp;
        entries[0].value = value;
        series->count++;
        series->tail = (series->tail + 1) & (MAX_ENTRIES - 1);
        return;
    }

    // Binary search (using logical indices) to find the insertion point
    int head = series->head;
    int left = 0;
    int right = count - 1;
    int insert_pos = count;  // Logical position for insertion (0 means beginning, count means at tail)

    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        int mid_idx = (head + mid) & (MAX_ENTRIES - 1);
        if (entries[mid_idx].timestamp < timestamp) {
            left = mid + 1;
        } else {
            right = mid - 1;
            insert_pos = mid;
        }
    }

    // Convert logical insertion position to physical index in the circular buffer
    int insert_index = (head + insert_pos) & (MAX_ENTRIES - 1);
    printf("Insertion Index: %d (logical pos: %d)\n", insert_index, insert_pos);

    // Shift elements to make room for the new entry.
    // Start at tail (the next free slot) and shift backwards until reaching insert_index.
    int i = series->tail;
    while (i != insert_index) {
        int prev = (i - 1) & (MAX_ENTRIES - 1);
        entries[i] = entries[prev];
        i = prev;
    }

    // Insert the new timestamp-value pair at the computed position.
    entries[insert_index].timestamp = timestamp;
    entries[insert_index].value = value;

    // Update the tail pointer and increase the count.
    series->tail = (series->tail + 1) & (MAX_ENTRIES - 1);
    series->count++;

    printf("After insertion, head: %d, tail: %d, count: %d\n", series->head, series->tail, series->count);
}

// Retrieve the value for a given key and timestamp. If an exact match is not found,
// return the value for the largest timestamp less than or equal to the given timestamp.
int get(const TimeSeriesDB *db, int key, int timestamp) {
    int idx = find_key_index(db, key);
    if (idx == EMPTY_KEY) return -1;  // Key not found

    const KeyTimeSeries *series = &db->key_series[idx];
    const TimestampValue *entries = series->entries;
    int count = series->count;
    int head = series->head;

    if (count == 0) return -1;  // No entries

    // If the requested timestamp is earlier than the oldest entry, return -1.
    if (timestamp < entries[head].timestamp) {
        return -1;
    }

    // If there is only one entry, check it.
    if (count == 1) {
        return (entries[head].timestamp <= timestamp) ? entries[head].value : -1;
    }

    // Binary search to find the closest timestamp <= given timestamp.
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

// Print all entries for each key in the database
void print_all_entries_in_db(const TimeSeriesDB *db) {
    for (int i = 0; i < MAX_KEYS; i++) {
        if (db->key_series[i].key != EMPTY_KEY) {
            const KeyTimeSeries *series = &db->key_series[i];
            printf("Key: %d\n", series->key);

            int j = series->head;
            int count = series->count;
            while (count--) {
                printf("    Timestamp: %d, Value: %d\n",
                       series->entries[j].timestamp, series->entries[j].value);
                j = (j + 1) & (MAX_ENTRIES - 1);
            }
        }
    }
}

// Test the implementation
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
    set(&db, 100, 224, 33);
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
