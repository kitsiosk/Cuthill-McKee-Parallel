#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

// Functions that returns the index smallest elemnt of array[]
// for which the value of visited[] is 0, i.e. has not been visited yet
int findMinUnvisited(int *array, int *visited, int n){
    // Find row with minimum degree
    int min = n+1;  // No degree can be more than N
    int argmin = -1;
    for(int i=0; i<n; ++i){
        if(array[i] < min && !visited[i]){
            min = array[i];
            argmin = i;
        }
    }

    return argmin;
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

// Functions that sorts the elements of values[] array 
// according with indexes coming from sorted keys[] array 
void parallelSort(int values[], int keys[], int n) 
{ 
    int i, j, min_idx; 
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (keys[j] < keys[min_idx]) 
            min_idx = j; 
  
        // Swap the found minimum element with the first element 
        swap(&values[min_idx], &values[i]);
        swap(&keys[min_idx], &keys[i]);
    } 
}

void print2D(int **A, int n){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

// Produce a bit with probability p of being 1 and 1-p of
// being 0
int rand_bit(double p){
    // Get random value in 0-1
    double r=((double)rand())/((double)RAND_MAX);
    return r < p ? 1 : 0;
}