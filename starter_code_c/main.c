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

void testAlgo(char* fileName, int nTotal, char* algoName){
    Record* records = malloc(sizeof(Record) * nTotal); //dynamic memory allocation for records
    printf("Reading records from file: %s\n", fileName);
    readFile(records, fileName);

    long startTime, endTime, executionTime;

    // Call the appropriate sorting function based on algoName
    if (strcmp(algoName, "InsertionSort") == 0) 
    {
        printf("InsertionSort started...\n");
        startTime = currentTimeMillis(); 
        insertionSort(records, nTotal);
        endTime = currentTimeMillis(); 
        executionTime = endTime - startTime; 
        printf("InsertionSort executed in %ld milliseconds.\n", executionTime);
        writeSortedDataFile(nTotal, records, algoName);
    } 
    else if (strcmp(algoName, "SelectionSort") == 0) 
    {
        printf("SelectionSort started...\n");
        startTime = currentTimeMillis(); 
        selectionSort(records, nTotal);
        endTime = currentTimeMillis(); 
        executionTime = endTime - startTime; 
        printf("selectionSort executed in %ld milliseconds.\n", executionTime);
        writeSortedDataFile(nTotal, records, algoName);
    } 
    else if (strcmp(algoName, "MergeSort") == 0) 
    {
        printf("MergeSort started...\n");
        startTime = currentTimeMillis(); 
        mergeSort(records, 0, nTotal-1);
        endTime = currentTimeMillis(); 
        executionTime = endTime - startTime; 
        printf("mergeSort Sort executed in %ld milliseconds.\n", executionTime);
        writeSortedDataFile(nTotal, records, algoName);
    } 
    else if (strcmp(algoName, "QuickSort") == 0) 
    {
        printf("QuickSort started...\n");
        startTime = currentTimeMillis();
        quickSort(records, 0, nTotal - 1);
        endTime = currentTimeMillis(); 
        executionTime = endTime - startTime; 
        printf("QuickSort executed in %ld milliseconds.\n", executionTime);
        writeSortedDataFile(nTotal, records, algoName);
    }
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
        // printAlgoStarter("INSERTION SORT");
        // testAlgo(filePath, nTotalRecords, "InsertionSort");
        // printAlgoEnder("INSERTION SORT");

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