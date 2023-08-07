#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 50

typedef struct 
{
  int fileId;
  int startBlock;
  int length;
} File;

void sequentialAllocation(File files[], int n);
void indexedAllocation(File files[], int n);
void linkedAllocation(File files[], int n);

int main() 
{
  int choice, n;  
  File files[MAX_FILES];
  printf("Enter the total number of files: ");  
  scanf("%d", &n);
  printf("Enter file details Id,StartBlock,Length:\n");
  for (int i = 0; i < n; i++)
  {
    printf("File %d: ", i+1);
    scanf("%d %d %d", &files[i].fileId, &files[i].startBlock, &files[i].length);
  }
  do 
  {
    printf("\nFile Allocation Strategies\n");
    printf("1. Sequential Allocation\n");
    printf("2. Indexed Allocation\n");
    printf("3. Linked Allocation\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) 
    {
      case 1:
        sequentialAllocation(files, n);
        break;
      case 2:
        indexedAllocation(files, n);
        break;
      case 3:
        linkedAllocation(files, n);
        break;
      case 4:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid choice! Please try again.\n");
        break;
    }
  } while (choice != 4);  
  return 0;
}

void sequentialAllocation(File files[], int n) 
{
  printf("\nFile Allocation Strategy: Sequential Allocation\n");
  int diskSize, allocatedBlocks = 0;
  printf("Enter the total number of blocks in the disk: ");
  scanf("%d", &diskSize);
  for (int i = 0; i < n; i++)
    {
      File file = files[i];
      if (file.startBlock + file.length - 1 <= diskSize)
      {
        allocatedBlocks += file.length;
        printf("File %d: Allocated blocks from %d to %d\n", file.fileId, file.startBlock, file.startBlock + file.length - 1);
      }
      else
      {
        printf("File %d: Not enough space available in disk\n", file.fileId);
      }
    }
  printf("Total allocated blocks: %d\n", allocatedBlocks);
}

void indexedAllocation(File files[], int n) 
{
  printf("\nFile Allocation Strategy: Indexed Allocation\n");
  int blockSize, allocatedBlocks = 0;
  printf("Enter the size of each block: ");
  scanf("%d", &blockSize);
  for (int i = 0; i < n; i++) {
    File file = files[i];
    int indexSize = (file.length + blockSize - 1) / blockSize;
    int* index = (int*)malloc(indexSize * sizeof(int));
    if (index == NULL) 
    {
      printf("Error allocating memory\n");
      return;
    }
    for (int j = 0; j < indexSize; j++) 
    {
      index[j] = rand() % blockSize;
    }
    allocatedBlocks += indexSize;
    printf("File %d: Allocated index blocks: ", file.fileId);
    for (int j = 0; j < indexSize; j++) 
    {
      printf("%d ", index[j]);
    }
    printf("\n");
    free(index);
  }
  printf("Total allocated blocks: %d\n", allocatedBlocks);
}

void linkedAllocation(File files[], int n) {
  printf("\nFile Allocation Strategy: Linked Allocation\n");
  for (int i = 0; i < n; i++) {
    File file = files[i];
    int* blocks = (int*)malloc(file.length * sizeof(int));
    if (blocks == NULL) 
    {
      printf("Error allocating memory\n");
      return;
    }
    for (int j = 0; j < file.length; j++) 
    {
      blocks[j] = rand() % 1000; // Random block numbers for simulation
    }
    printf("File %d: Allocated blocks: ", file.fileId);
    for (int j = 0; j < file.length; j++) 
    {
      printf("%d ", blocks[j]);
    }
    printf("\n");
    free(blocks);
  }
}
