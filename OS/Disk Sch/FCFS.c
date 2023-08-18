#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 10
void fcfsDiskScheduling(int requests[], int numRequests, int headPosition) {
  int totalSeekTime = 0;
  int currentHeadPosition = headPosition;
  printf("Sequence: %d ", currentHeadPosition);
  for (int i = 0; i < numRequests; i++) {
    int seekTime = abs(requests[i] - currentHeadPosition);
    totalSeekTime += seekTime;
    printf("%d ", requests[i]);
    currentHeadPosition = requests[i];
  }
  printf("\nTotal seek time: %d\n", totalSeekTime);
}
int main() {
  int requests[MAX_REQUESTS] = {98, 183, 37, 122, 14, 124, 65, 67, 89, 99};
  int numRequests = sizeof(requests) / sizeof(requests[0]);
  int headPosition = 53;
  fcfsDiskScheduling(requests, numRequests, headPosition);
  return 0;
}