#include "record.c"
#include "sortingalgorithms.c"
#include "filereader.c"
#include "timer.c"
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#define MAXFILENAME 500

void printAlgoStarter(char* algoName){
    printf("============================================\n");
    printf("          Start of %s                      \n", algoName);
    printf("============================================\n");
}

void printAlgoEnder(char* algoName){
    printf("============================================\n");
    printf("          End of %s                      \n", algoName);
    printf("============================================\n");
}

void writeSortedDataFile(int nTotal, Record *records, char* algoName) {
    FILE *outputFile;
    char outputFileName[MAXFILENAME];

    int i;
    // Prepare output file name
    strcpy(outputFileName, "results\\");
    strcat(strcat(outputFileName, algoName), "Sorted.txt");
    outputFile = fopen(outputFileName, "wt");

    for (i = 0; i < nTotal; i++) 
        fprintf(outputFile, "%d %s\n", records[i].idNumber, records[i].name);
    fclose(outputFile);
}

void runAlgo3Param(Record *records, int nTotal, char* algoName, void (*sortFunc)(Record *, int, int *)) {
    int frequencyCount = 0; // Initialize frequency count
    long startTime, endTime, executionTime;

    printf("%s started...\n", algoName);
    startTime = currentTimeMillis(); 
    sortFunc(records, nTotal, &frequencyCount);
    endTime = currentTimeMillis(); 
    executionTime = endTime - startTime; 
    printf("%s executed in %ld milliseconds.\n", algoName, executionTime);
    printf("Frequency count: %d\n", frequencyCount);
    writeSortedDataFile(nTotal, records, algoName);
}
void runAlgo4Param(Record *records, int start, int end, char* algoName, void (*sortFunc)(Record *, int, int, int *)) {
    int frequencyCount = 0; // Initialize frequency count
    long startTime, endTime, executionTime;

    printf("%s started...\n", algoName);
    startTime = currentTimeMillis(); 
    sortFunc(records, start, end, &frequencyCount);
    endTime = currentTimeMillis(); 
    executionTime = endTime - startTime; 
    printf("%s executed in %ld milliseconds.\n", algoName, executionTime);
    printf("Frequency count: %d\n", frequencyCount);
    writeSortedDataFile(end+1, records, algoName);
}

void testAlgo(char* fileName, int nTotal, char* algoName){
    Record *records = malloc(sizeof(Record) * nTotal); //dynamic memory allocation for records

    printf("Reading records from file: %s\n", fileName);
    readFile(records, fileName);

    // Call the appropriate sorting function based on algoName
    if (strcmp(algoName, "InsertionSort") == 0) 
        runAlgo3Param(records, nTotal, algoName, insertionSort);
    else if (strcmp(algoName, "SelectionSort") == 0) 
        runAlgo3Param(records, nTotal, algoName, selectionSort);
    else if (strcmp(algoName, "MergeSort") == 0) 
        runAlgo4Param(records, 0, nTotal-1, algoName, mergeSort);
    else if (strcmp(algoName, "QuickSort") == 0) 
        runAlgo4Param(records, 0, nTotal-1, algoName, quickSort);

    free(records); // Free allocated memory for records
}

int main()
{
    FILE *filePtr;
    char filePath[MAXFILENAME + 10];
    char fileName[MAXFILENAME];
    int nTotalRecords;
    strcpy(filePath, "data\\"); // Default file name
    printf("Enter the file name to read records from (without \"data\" directory and .txt): ");
    scanf("%499s", fileName);
    strcat(filePath, fileName);
    strcat(filePath, ".txt"); // Append .txt extension

    if ((filePtr = fopen(filePath, "rt")) != NULL)
    {
        fscanf(filePtr, "%d", &nTotalRecords);
        printf("Total records to sort: %d\n", nTotalRecords);
        rewind(filePtr); // Reset file pointer to the beginning

        // Test Insertion Sort
        printAlgoStarter("INSERTION SORT");
        testAlgo(filePath, nTotalRecords, "InsertionSort");
        printAlgoEnder("INSERTION SORT");

        // Test Selection Sort
        printAlgoStarter("SELECTION SORT");
        testAlgo(filePath, nTotalRecords, "SelectionSort");
        printAlgoEnder("SELECTION SORT");

        // Test Merge Sort
        printAlgoStarter("MERGE SORT");
        testAlgo(filePath, nTotalRecords, "MergeSort");
        printAlgoEnder("MERGE SORT");

        // Bonus: Quick Sort
        printAlgoStarter("QUICK SORT");
        testAlgo(filePath, nTotalRecords, "QuickSort");
        printAlgoEnder("QUICK SORT");

        fclose(filePtr);
        printf("All algorithms tested successfully.\n");
    }
    else {
        printf("Error opening file %s\n", filePath);
    }
    return 0;
}