#include <stdio.h>

#define MAX_KEYS 100   // Maximum number of keys allowed
#define MAX_ENTRIES 50 // Maximum number of timestamp-value pairs per key

// Structure to hold a time-value pair
typedef struct {
    int time;  // Timestamp
    int value; // Associated value
} TimeValuePair;

// Structure to hold all time-value pairs for a specific key
typedef struct {
    int key;  // Unique key identifier
    TimeValuePair entries[MAX_ENTRIES]; // Array of time-value pairs
    int size; // Number of time-value pairs stored for this key
} TimeMapEntry;

// Structure to manage multiple keys and their respective time-value mappings
typedef struct {
    TimeMapEntry map[MAX_KEYS]; // Array to store multiple keys
    int size; // Number of keys stored
} TimeMap;

// Initializes the time-based map by setting the size to 0
void init_time_map(TimeMap *d) {
    d->size = 0;
}

// Searches for a given key in the TimeMap
// Returns the index of the key if found, otherwise returns -1
int find_key_index(TimeMap *d, int key) {
    int idx = -1;
    
    for (int i = 0; i < d->size; i++) {
        if (d->map[i].key == key) {
            idx = i; // Found the key, return its index
            break;
        }
    }

    return idx; // Return index if found, otherwise -1
}

// Inserts a new (time, value) pair into the TimeMap
void set(TimeMap *d, int key, int time, int value) {
    int idx = find_key_index(d, key);

    // If key does not exist, create a new entry
    if (idx == -1) {      
        idx = d->size++; // Assign the next available index and increment size
        d->map[idx].key = key;
        d->map[idx].size = 0; // Initialize the entry count for this key
    }

    // Insert the (time, value) pair at the next available position
    int entry_idx = d->map[idx].size++;
    d->map[idx].entries[entry_idx].time = time;
    d->map[idx].entries[entry_idx].value = value;
}

// Old version of the `get` function (for reference)
int get_old(TimeMap *d, int key, int time) {
    int idx = find_key_index(d, key);

    if (idx == -1)
        return -1; // Key not found
    
    // Perform binary search on sorted timestamps
    int left = 0, right = d->map[idx].size - 1, best = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (d->map[idx].entries[mid].time == time) {
            best = mid;
            break;
        } else if (d->map[idx].entries[mid].time < time) {
            best = mid;   // Store the best found index so far
            left = mid + 1; // Search in the right half for a larger valid time
        }
        else {
            right = mid - 1; // Search in the left half
        }
    }

    if (best == -1)
        return -1; // No valid timestamp found

    return d->map[idx].entries[best].value;
}

// Optimized version of `get` function using binary search
int get(TimeMap *d, int key, int time) {
    int idx = find_key_index(d, key);

    if (idx == -1)
        return -1; // Key not found
    
    // Perform binary search on sorted timestamps
    TimeValuePair *entries = d->map[idx].entries; // Get reference to entries array
    int left = 0, right = d->map[idx].size - 1, best = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (entries[mid].time == time) {
            return entries[mid].value; // Found exact match, return immediately
        } else if (entries[mid].time < time) {
            best = mid;      // Store best-found index
            left = mid + 1;  // Search in the right half for a better match
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return (best == -1) ? -1 : entries[best].value; // Return best-found value or -1
}

// Main function to test the TimeMap implementation
int main() {
    TimeMap d;
    init_time_map(&d); // Initialize the time-based map

    // Insert some key-value pairs for testing
    set(&d, 1, 100, 10);
    set(&d, 1, 102, 15);
    set(&d, 1, 105, 20);
    set(&d, 1, 106, 25);
    set(&d, 1, 110, 30);

    // Query the TimeMap
    printf("%d\n", get(&d, 1, 107)); // Expected output: 25 (last entry before 107)

    return 0;
}
