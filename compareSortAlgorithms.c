#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void mergeHelper(int *pData, int a, int b, int c)
{
	int part1 = b - a + 1; 
	int part2 = c - b; 

	int *L = malloc(part1 * sizeof(int)); 
	int *R = malloc(part2 * sizeof(int)); 

	for (int i = 0; i < part1; i++)
	{
		L[i] = pData[a + i]; 
	}

	for (int j = 0; j < part2; j++)
	{
		R[j] = pData[b + j]; 
	}

	int i = 0, j = 0, k = a; 

	while (i < part1 && j < part2)
	{
		if (L[i] <= R[j])
		{
			pData[k] = L[i]; 
			i++; 
		}
		
		else
		{
			pData[k] = R[j]; 
			j++; 
		}
		k++; 
	}
	
	while (i < part1)
	{
		pData[k] = L[i]; 
		i++; 
		k++; 
	}

	while (j < part2)
	{
		pData[k] = R[j]; 
		j++; 
		k++; 
	}
	
	free(L); 
	free(R); 
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
		if (l < r)
		{
			int eq = (l + r) / 2; 

			mergeSort(pData, l, eq); 
			mergeSort(pData, eq + 1, r); 

			mergeHelper(pData, l, eq, r); 
		}
		
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
		for(int i = 1; i < n; i++)
		{
			int k = pData[i]; 
			int j = i - 1; 
		
			while (j >= 0 && pData[j] > k)
			{
				pData[j + 1] = pData[j]; 
				j--; 
			}
			
			pData[j + 1] = k; 
		}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
		for (int i = 0; i < n - 1; i++) 
		{
      for (int j = 0; j < n - i - 1; j++) 
			{
        if (pData[j] > pData[j + 1]) 
				{
          int tmp = pData[j];
          pData[j] = pData[j + 1];
          pData[j + 1] = tmp;
        }
      }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	for (int i = 0; i < n - 1; i++) 
	{
    int minimumIndex = i;
    for (int j = i + 1; j < n; j++) 
		{
      if (pData[j] < pData[minimumIndex])
			{
				minimumIndex = j;
			}
     
    }

    int tmp = pData[i];
    pData[i] = pData[minimumIndex];
    pData[minimumIndex] = tmp;
  }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block

		for (int i = 0; i < dataSz; i++)
    {
			fscanf(inFile, "%d", &((*ppData)[i]));
    }

    fclose(inFile);  
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}