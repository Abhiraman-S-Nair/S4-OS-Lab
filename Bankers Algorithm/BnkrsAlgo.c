#include <stdio.h>

// Function to check if the requested resources are less than or equal to the available resources
int isSafeState(int n, int m, int allocation[n][m], int max[n][m], int available[m]) {
    int work[m], finish[n];
    
    // Initialize work and finish arrays
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    
    int count = 0; // Count of finished processes
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    // All resources can be allocated to process i
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            // No safe sequence found
            return 0;
        }
    }
    return 1;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    
    int allocation[n][m], max[n][m], available[m];
    
    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    // Input max matrix
    printf("Enter the max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    // Input available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    // Check if the system is in a safe state
    if (isSafeState(n, m, allocation, max, available)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
    
    return 0;
}
