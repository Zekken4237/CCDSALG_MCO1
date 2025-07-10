#ifndef SORTINGALGORITHMS_C
#define SORTINGALGORITHMS_C

#include <stdio.h>
#include <stdlib.h>
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
int i, j;
Record key;


    for(i = 1; i <m; i++){

        key = arr[i];

        j = i -1;


        while(j>= 0 && arr[j].idNumber > key,idNumber){

            arr[j + 1] = arr[j];

            j--;

        }

        arr[j+1] = key;

    }

}



void selectionSort(Record *arr, int n)
{
    // TODO: Implement this sorting algorithm here.

    Record temp;
    int tempIndex;
    int i, j;

    for(i = 0; i < n; i++){
        tempIndex = i;
        for(j = i+1; j < n; j++){
            if(arr[j].idNumber < arr[tempIndex].idNumber){
                tempIndex = j;
            }
        }
        
        if(tempIndex != i){
            temp = arr[i];
            arr[i] = arr[tempIndex];
            arr[tempIndex] = temp;
        }
    }
}

void merge(Record *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Record *L = malloc(sizeof(Record) * n1);
    Record *R = malloc(sizeof(Record) * n2);

    for (i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i].idNumber <= R[j].idNumber) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(Record *arr, int p, int r)
{
    int mid;
    
    if (p < r) {
        mid = p + (r - p) / 2;
        mergeSort(arr, p, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, p, mid, r);
    }
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
