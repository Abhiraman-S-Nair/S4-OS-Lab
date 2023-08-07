#include <stdio.h>
#include <stdbool.h>

#define NUM_FRAMES 3

// Function to find index of a page in a frame
int findPageIndex(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// Function to find the index of the page to be replaced using Optimal algorithm
int findOptimalIndex(int pages[], int numPages, int frames[], int numFrames, int currentIndex) {
    int farthestIndex = -1;
    int farthestDistance = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentIndex + 1; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                if (j - currentIndex > farthestDistance) {
                    farthestDistance = j - currentIndex;
                    farthestIndex = i;
                }
                break;
            }
        }

        if (j == numPages) {
            return i; // Page not found in future references
        }
    }

    return farthestIndex;
}

// Function to simulate page replacement using FIFO algorithm
int fifo(int pages[], int numPages) {
    int frames[NUM_FRAMES];
    int numFaults = 0;

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1; // Initialize frames as empty
    }

    int frameIndex = 0; // Index to replace frames in FIFO order

    for (int i = 0; i < numPages; i++) {
        int pageIndex = findPageIndex(pages[i], frames, NUM_FRAMES);

        if (pageIndex == -1) {
            frames[frameIndex] = pages[i];
            frameIndex = (frameIndex + 1) % NUM_FRAMES;
            numFaults++;
        }

        // Print frames
        printf("Frames: ");
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    return numFaults;
}

// Function to simulate page replacement using LRU algorithm
int lru(int pages[], int numPages) {
    int frames[NUM_FRAMES];
    int numFaults = 0;

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1; // Initialize frames as empty
    }

    int timeCounter = 0;
    int lastUsedTime[NUM_FRAMES];

    for (int i = 0; i < NUM_FRAMES; i++) {
        lastUsedTime[i] = -1; // Initialize last used time
    }

    for (int i = 0; i < numPages; i++) {
        int pageIndex = findPageIndex(pages[i], frames, NUM_FRAMES);

        if (pageIndex == -1) {
            int lruIndex = 0;
            for (int j = 1; j < NUM_FRAMES; j++) {
                if (lastUsedTime[j] < lastUsedTime[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            lastUsedTime[lruIndex] = timeCounter;
            numFaults++;
        } else {
            lastUsedTime[pageIndex] = timeCounter;
        }

        timeCounter++;

        // Print frames
        printf("Frames: ");
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    return numFaults;
}

// Function to simulate page replacement using Optimal algorithm
int optimal(int pages[], int numPages) {
    int frames[NUM_FRAMES];
    int numFaults = 0;

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < numPages; i++) {
        int pageIndex = findPageIndex(pages[i], frames, NUM_FRAMES);

        if (pageIndex == -1) {
            int optimalIndex = findOptimalIndex(pages, numPages, frames, NUM_FRAMES, i);
            frames[optimalIndex] = pages[i];
            numFaults++;
        }

        // Print frames
        printf("Frames: ");
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    return numFaults;
}

int main() {
    int pages[] = {0, 1, 2, 3, 2, 4, 5, 3, 4, 1}; // Reference string
    int numPages = sizeof(pages) / sizeof(pages[0]);

    printf("Pages: ");
    for (int i=0;i<numPages;i++)
    {
        printf(" %d ",pages[i]);
    }
    int choice;
    do {
        printf("\nPage Replacement Algorithms:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int numFaults = 0;
        switch (choice) {
            case 1:
                numFaults = fifo(pages, numPages);
                break;
            case 2:
                numFaults = lru(pages, numPages);
                break;
            case 3:
                numFaults = optimal(pages, numPages);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

        if (choice >= 1 && choice <= 3) {
            printf("Total number of page faults: %d\n\n", numFaults);
        }
    } while (choice != 4);

    return 0;
}
