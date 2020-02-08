#ifndef HELPER
#define HELPER

#include "helper.c"

void parallelSort(int values[], int keys[], int n);
void swap(int *xp, int *yp);
int findMinUnvisited(int *array, int *visited, int n);
int *RCM(int **A);
void print2D(int **A, int n);
int rand_bit(double p);
void push_queue(int key);
int isEmpty_queue();
int pop_queue();

#endif