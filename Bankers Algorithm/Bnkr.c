#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int safeSequence[MAX_PROCESSES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];

int numProcesses;
int numResources;

void input()
{
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the memory available in each resource: ");
    for (i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources required by each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < numResources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the resources allocated to each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int safetyCheck()
{
    int i, j, k;
    int count = 0;

    for (i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < numProcesses; i++) {
        finish[i] = 0;
    }

    while (count < numProcesses) {
        int found = 0;

        for (i = 0; i < numProcesses; i++) {
            if (finish[i] == 0) {
                int safe = 1;

                for (j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        safe = 0;
                        break;
                    }
                }

                if (safe) {
                    for (k = 0; k < numResources; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("System is in an unsafe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (i = 0; i < numProcesses; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return 1;
}

int requestResources(int processId)
{
    int i;

    printf("Enter the resources requested by process %d: ", processId);
    for (i = 0; i < numResources; i++) {
        scanf("%d", &allocation[processId][i]);
        need[processId][i] = maximum[processId][i] - allocation[processId][i];
    }

    for (i = 0; i < numResources; i++) {
        if (allocation[processId][i] > available[i]) {
            printf("Process %d must wait. Not enough resources available.\n", processId);
            return 0;
        }
    }

    for (i = 0; i < numResources; i++) {
        available[i] -= allocation[processId][i];
        need[processId][i] -= allocation[processId][i];
    }

    if (safetyCheck()) {
        printf("Resources allocated to process %d.\n", processId);
        return 1;
    } else {
        for (i = 0; i < numResources; i++) {
            available[i] += allocation[processId][i];
            need[processId][i] += allocation[processId][i];
        }
        return 0;
    }
}

int main()
{
    int processId;

    input();
    safetyCheck();

    printf("\nEnter the process id to request resources (-1 to exit): ");
    scanf("%d", &processId);

    while (processId != -1) {
        requestResources(processId);

        printf("\nEnter the process id to request resources (-1 to exit): ");
        scanf("%d", &processId);
    }

    return 0;
}
