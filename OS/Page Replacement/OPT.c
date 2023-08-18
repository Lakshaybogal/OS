#include<stdio.h>
#define MAX_FRAMES 3
    int pageExists(int page, int frames[], int numFrames) {
  for (int i = 0; i < numFrames; i++) {
    if (frames[i] == page) {
      return 1;
    }
  }
  return 0;
}
void displayFrame(int frames[], int numFrames) {
  printf("Current frame state: ");
  for (int i = 0; i < numFrames; i++) {
    if (frames[i] != -1) {
      printf("%d ", frames[i]);
    }
  }
  printf("\n");
}
void optPageReplacement(int pages[], int numPages) {
  int frames[MAX_FRAMES];
  for (int i = 0; i < MAX_FRAMES; i++) {
    frames[i] = -1;
  }
  int pageFaults = 0;
  for (int i = 0; i < numPages; i++) {
    printf("Page: %d\n", pages[i]);
    if (!pageExists(pages[i], frames, MAX_FRAMES)) {
      int framePointer = -1;
      int farthestIndex = i;
      for (int j = 0; j < MAX_FRAMES; j++) {
        int pageFound = 0;
        for (int k = i + 1; k < numPages; k++) {
          if (frames[j] == pages[k]) {
            pageFound = 1;
            if (k > farthestIndex) {
              farthestIndex = k;
              framePointer = j;
            }
            break;
          }
        }
        if (!pageFound) {
          framePointer = j;
          break;
        }
      }
      frames[framePointer] = pages[i];
      pageFaults++;
    }
    displayFrame(frames, MAX_FRAMES);
  }
  printf("Total page faults: %d\n", pageFaults);
}
int main() {
  int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
  int numPages = sizeof(pages) / sizeof(pages[0]);
  optPageReplacement(pages, numPages);
  return 0;
}