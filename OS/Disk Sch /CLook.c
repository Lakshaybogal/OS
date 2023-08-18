#include <stdio.h>
#include <stdlib.h>

#define size 8
#define disk_size 200

void CLOOK(int arr[], int head) {
    int seek_count = 0;
    int distance, cur_track;
    int left[size], right[size];
    int left_size = 0, right_size = 0;
    int seek_sequence[size];

    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left[left_size++] = arr[i];
        if (arr[i] > head)
            right[right_size++] = arr[i];
    }

    // Sort the right array to ensure proper C-LOOK behavior
    for (int i = 0; i < right_size - 1; i++) {
        for (int j = i + 1; j < right_size; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    // Perform seeks in the right direction
    for (int i = 0; i < right_size; i++) {
        cur_track = right[i];
        seek_sequence[i] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    // Move head to the end of the disk
    seek_count += abs(head - disk_size);
    head = 0;

    // Perform seeks in the left direction
    for (int i = 0; i < left_size; i++) {
        cur_track = left[i];
        seek_sequence[right_size + i] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    printf("Total number of seek operations = %d\n", seek_count);
    printf("Seek Sequence is\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", seek_sequence[i]);
    }
}

int main() {
    int arr[size] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;

    printf("Initial position of head: %d\n", head);
    CLOOK(arr, head);

    return 0;
}
