#ifndef SORTINGALGORITHMS_C
#define SORTINGALGORITHMS_C

#include <stdio.h>
#include "record.c"

/*
* You may declare additional variables and helper functions
* as needed by the sorting algorithms here.
*/


//helper functions of quicksort
void swap(Record *a, Record *b)
{
    Record tempRecord = *a;
    *a = *b;
    *b = tempRecord;
}

int partitionArr(Record *arr, int p, int r)
{
    int mid = p + (r - p) / 2;
    swap(&arr[mid], &arr[r]); // Move pivot to end for partitioning
    //change the pivot to a much more efficient one based on other algorithms
    Record pivotData = arr[r]; // Using the middle element as pivot
    int i,j;

    i = p;

    for (j = p; j < r; j++)
        if(arr[j].idNumber <= pivotData.idNumber)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    swap(&arr[i], &arr[r]);
    return i;
}

void insertionSort(Record *arr, int n)
{
    // TODO: Implement this sorting algorithm here.
}

void selectionSort(Record *arr, int n)
{
    // TODO: Implement this sorting algorithm here.
}

void mergeSort(Record *arr, int p, int r)
{
    // TODO: Implement this sorting algorithm here.
}

/*
* Define AT LEAST ONE more sorting algorithm here, apart from the
* ones given above. Make sure that the method accepts an array of
* record structures.
*/
void quickSort(Record *arr, int p, int r)
{
    while (p < r)
    {
        int pivotIndex = partitionArr(arr, p, r);
        
        // Always recurse on the smaller partition first to minimize stack usage
        if (pivotIndex - p < r - pivotIndex)
        {
            quickSort(arr, p, pivotIndex - 1);
            p = pivotIndex + 1;  // Continue with the larger partition
        }
        else
        {
            quickSort(arr, pivotIndex + 1, r);
            r = pivotIndex - 1;  // Continue with the larger partition
        }
    }
}

#endif