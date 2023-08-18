#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int pageFaults(int pages[], int n, int capacity) {
    int s[SIZE];
    int indexes[SIZE];
    int page_faults = 0;
    int i, j, lru, val;

    for (i = 0; i < SIZE; i++) {
        s[i] = -1;
        indexes[i] = -1;
    }

    for (i = 0; i < n; i++) {
        if (indexes[pages[i]] == -1) {
            if (s[capacity - 1] == -1) {
                for (j = 0; j < capacity; j++) {
                    if (s[j] == -1) {
                        s[j] = pages[i];
                        indexes[pages[i]] = j;
                        page_faults++;
                        break;
                    }
                }
            } else {
                lru = SIZE;
                for (j = 0; j < capacity; j++) {
                    if (indexes[s[j]] < lru) {
                        lru = indexes[s[j]];
                        val = s[j];
                    }
                }
                for (j = 0; j < capacity; j++) {
                    if (s[j] == val) {
                        s[j] = pages[i];
                        indexes[pages[i]] = j;
                        indexes[val] = -1;
                        page_faults++;
                        break;
                    }
                }
            }
        }
    }
    return page_faults;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;
    printf("Number of Pages: %d\n", capacity);
    int page_hits = n - pageFaults(pages, n, capacity);
    int page_faults = pageFaults(pages, n, capacity);
    printf("Number of Page Hits: %d\n", page_hits);
    printf("Number of Page Faults: %d\n", page_faults);
    return 0;
}
