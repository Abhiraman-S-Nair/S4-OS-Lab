#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 50

void fcfs(int requests[], int n, int head);
void sstf(int requests[], int n, int head);
void scan(int requests[], int n, int head, int direction);
void cscan(int requests[], int n, int head);
void look(int requests[], int n, int head, int direction);
void clook(int requests[], int n, int head);

int main() {
    int choice, n, head;
    int requests[MAX_REQUESTS];

    printf("Enter the total number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    do {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. LOOK\n");
        printf("6. C-LOOK\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(requests, n, head);
                break;
            case 2:
                sstf(requests, n, head);
                break;
            case 3:
                scan(requests, n, head, 1);
                break;
            case 4:
                cscan(requests, n, head);
                break;
            case 5:
                look(requests, n, head, 1);
                break;
            case 6:
                clook(requests, n, head);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

void fcfs(int requests[], int n, int head) {
    printf("\nDisk Scheduling Algorithm: FCFS\n");

    int totalSeekTime = 0;

    for (int i = 0; i < n; i++) {
        int currentRequest = requests[i];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

void sstf(int requests[], int n, int head) {
    printf("\nDisk Scheduling Algorithm: SSTF\n");

    int totalSeekTime = 0;
    int* visited = (int*)calloc(n, sizeof(int));

    if (visited == NULL) {
        printf("Error allocating memory\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        int minSeekTime = INT_MAX;
        int minIndex = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int seekTime = abs(requests[j] - head);

                if (seekTime < minSeekTime) {
                    minSeekTime = seekTime;
                    minIndex = j;
                }
            }
        }

        visited[minIndex] = 1;
        int currentRequest = requests[minIndex];

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, minSeekTime);

        totalSeekTime += minSeekTime;
        head = currentRequest;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);

    free(visited);
}

void scan(int requests[], int n, int head, int direction) {
    printf("\nDisk Scheduling Algorithm: SCAN\n");

    int totalSeekTime = 0;
    int minRequest = INT_MAX;
    int maxRequest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (requests[i] < minRequest) {
            minRequest = requests[i];
        }
        if (requests[i] > maxRequest) {
            maxRequest = requests[i];
        }
    }

    int currentIndex = 0;
    while (requests[currentIndex] < head && currentIndex < n) {
        currentIndex++;
    }

    if (direction == 0) {
        currentIndex--;
    }

    while (currentIndex >= 0) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex--;
    }

    if (direction == 0) {
        printf("Move disk head from %d to %d -> Seek Time: 0\n", head, minRequest);
        totalSeekTime += abs(head - minRequest);
        head = minRequest;
    } else {
        printf("Move disk head from %d to %d -> Seek Time: 0\n", head, maxRequest);
        totalSeekTime += abs(head - maxRequest);
        head = maxRequest;
    }

    int endIndex = currentIndex + 1;
    while (endIndex < n) {
        int currentRequest = requests[endIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        endIndex++;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

void cscan(int requests[], int n, int head) {
    printf("\nDisk Scheduling Algorithm: C-SCAN\n");

    int totalSeekTime = 0;
    int minRequest = INT_MAX;
    int maxRequest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (requests[i] < minRequest) {
            minRequest = requests[i];
        }
        if (requests[i] > maxRequest) {
            maxRequest = requests[i];
        }
    }

    int currentIndex = 0;
    while (requests[currentIndex] < head && currentIndex < n) {
        currentIndex++;
    }

    while (currentIndex < n) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex++;
    }

    printf("Move disk head from %d to %d -> Seek Time: %d\n", head, maxRequest, abs(head - maxRequest));
    totalSeekTime += abs(head - maxRequest);
    head = maxRequest;

    printf("Move disk head from %d to %d -> Seek Time: %d\n", head, minRequest, abs(head - minRequest));
    totalSeekTime += abs(head - minRequest);
    head = minRequest;

    currentIndex = 0;
    while (requests[currentIndex] < head && currentIndex < n) {
        currentIndex++;
    }

    while (currentIndex < n) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex++;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

void look(int requests[], int n, int head, int direction) {
    printf("\nDisk Scheduling Algorithm: LOOK\n");

    int totalSeekTime = 0;
    int minRequest = INT_MAX;
    int maxRequest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (requests[i] < minRequest) {
            minRequest = requests[i];
        }
        if (requests[i] > maxRequest) {
            maxRequest = requests[i];
        }
    }

    int currentIndex = 0;
    while (requests[currentIndex] < head && currentIndex < n) {
        currentIndex++;
    }

    if (direction == 0) {
        currentIndex--;
    }

    while (currentIndex >= 0) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex--;
    }

    currentIndex = currentIndex + 2;
    while (currentIndex < n) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex++;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

void clook(int requests[], int n, int head) {
    printf("\nDisk Scheduling Algorithm: C-LOOK\n");

    int totalSeekTime = 0;
    int minRequest = INT_MAX;
    int maxRequest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (requests[i] < minRequest) {
            minRequest = requests[i];
        }
        if (requests[i] > maxRequest) {
            maxRequest = requests[i];
        }
    }

    int currentIndex = 0;
    while (requests[currentIndex] < head && currentIndex < n) {
        currentIndex++;
    }

    while (currentIndex < n) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex++;
    }

    currentIndex = 0;
    while (requests[currentIndex] < head && currentIndex < n) {
        currentIndex++;
    }

    while (currentIndex < n) {
        int currentRequest = requests[currentIndex];
        int seekTime = abs(currentRequest - head);

        printf("Move disk head from %d to %d -> Seek Time: %d\n", head, currentRequest, seekTime);

        totalSeekTime += seekTime;
        head = currentRequest;
        currentIndex++;
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}
