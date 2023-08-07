#include <stdio.h>
#include <string.h>
int main()
{
    int m;
    int n;
    int blocks, processes;
    printf("Enter the number of blocks and processes resp: ");
    scanf("%i %i", &blocks, &processes);
    printf("Enter the block sizes: ");
    int blockSize[blocks], a[blocks];
    for(int i=0; i<blocks; i++){
        scanf("%i", &blockSize[i]);
        a[i] = blockSize[i];
    }
    printf("Enter the process sizes: ");
    int processSize[processes], b[blocks];

    for(int i=0; i<processes; i++){
        scanf("%i", &processSize[i]);
        b[i] = processSize[i];
    }

    m = sizeof(blockSize) / sizeof(blockSize[0]);
    n = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, m, processSize, n);

    for(int i=0; i<processes; i++){
        processSize[i] = b[i];
    }
    for(int i=0; i<blocks; i++){
        blockSize[i] = a[i];
    }
    m = sizeof(blockSize) / sizeof(blockSize[0]);
    n = sizeof(processSize) / sizeof(processSize[0]);

    bestFit(blockSize, m, processSize, n);

    for(int i=0; i<processes; i++){
        processSize[i] = b[i];
    }
    for(int i=0; i<blocks; i++){
        blockSize[i] = a[i];
    }
    m = sizeof(blockSize) / sizeof(blockSize[0]);
    n = sizeof(processSize) / sizeof(processSize[0]);


    worstFit(blockSize, m, processSize, n);

    return 0 ;
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    printf("\n\nBEST FIT MEMORY ALLOCATION\n\n");
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {

        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }


        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %i\t\t%i\t\t",i+1,processSize[i]);
        if (allocation[i] != -1)
            printf("%i",allocation[i]+1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[],
              int n)
{
    int allocation[n];
    printf("\n\nWORST FIT MEMORY ALLOCATION\n\n");
    memset(allocation, -1, sizeof(allocation));
    for (int i=0; i<n; i++)
    {
        int wstIdx = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        if (wstIdx != -1)
        {
            allocation[i] = wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %i\t\t%i\t\t",i+1,processSize[i]);
        if (allocation[i] != -1)
            printf("%i",allocation[i]+1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int i, j;
    printf("\n\nFIRST FIT MEMORY ALLOCATION\n\n");
    int allocation[n];
    for(i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %i\t\t  ", i+1);
        printf("%i\t\t  ", processSize[i]);
        if (allocation[i] != -1)
            printf("%i", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}
