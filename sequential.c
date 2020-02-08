#include <omp.h>
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 10000

// Define queue as global variable
int queue[N], front = -1,rear = -1;
void push_queue(int key);
int pop_queue();
int isEmpty_queue();

int main(){
    printf("Entering program \n");
    srand(0);
    double sparsity = 0.01;
    int **A = (int **) malloc(N*sizeof(int *));

    for(int i=0; i<N; ++i)
        A[i] = (int *) malloc(N*sizeof(int));

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            A[i][j] = rand_bit(sparsity);
        }
    }

    // Initialize permutation vector
    int *R = (int *) malloc(N*sizeof(int));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    R = RCM(A);

    gettimeofday(&end, NULL);
    double elapsedTime = end.tv_sec -start.tv_sec +(end.tv_usec-start.tv_usec)/1e6;
    printf("Time elapsed: %lf \n", elapsedTime);

    return 0;
}

int *RCM(int **A){
    // Initialize visited array
    int visited[N];
    for(int i=0; i<N; ++i){
        visited[i] = 0;
    }

    // Initialize result array. Set all values to -1
    int *R = (int *)malloc(N*sizeof(int));
    int next_free = 0;  // No result inserted yet. Increment by one at each insertion
    for(int i=0; i<N; ++i){
        R[i] = -1;
    }

    // Initialize degrees array. The degree of node i is the sum
    // of the 1s of row i minus one for the diagonal entry(self mapping).
    int D[N];
    for(int i=0; i<N; ++i){
        int degree = 0;
        for(int j=0; j<N; ++j){
            if (A[i][j] == 1) degree+=1;
        }
        D[i] = degree - 1;
    }

    // Find row with minimum degree
    int min = N+1;  // No degree can be more than N
    int argmin = -1;
    for(int i=0; i<N; ++i){
        if(D[i] < min){
            min = D[i];
            argmin = i;
        }
    }

    // Push the node with the lowest degree in the queue
    push_queue(argmin);
    visited[argmin] = 1;


    while( !isEmpty_queue() ){
        int p = pop_queue();

        R[next_free] = p;
        next_free++;

        // Array with neighbooring nodes of p. Its size is equal
        // to the degree o p
        int neighboors[D[p]];
        int neighboorsDegrees[D[p]];
        int next_free_nb = 0;

        // Loop through every node j
        int j;
        for(j=0; j<N; ++j){
            // If node j is adjacent to p
            if(A[p][j] == 1 && p!=j){
                // Add j to neighboors array
                    neighboors[next_free_nb] = j;
                    neighboorsDegrees[next_free_nb] = D[j];
                    next_free_nb++;
            }
        }

        // Sort neighboors array according to neighboorsDegrees array
        parallelSort(neighboors, neighboorsDegrees, D[p]);

        for(int i=0; i<D[p]; ++i){
            if(!visited[neighboors[i]]){
                visited[neighboors[i]] = 1;
                push_queue(neighboors[i]);
            }
        }

        // Check for unexplored nodes. If the graph in not connected
        // we need to check for each connected subgraph separetly
        // findMinUnvisited() functions returns -1 if all graphs are
        // visited and the index of the node of with the lowest 
        // degree that has not been visited yet
        if(isEmpty_queue()){
            argmin = findMinUnvisited(D, visited, N);
            if(argmin != -1){
                push_queue(argmin);
                visited[argmin] = 1;
            } 
        }
    }
    return R;
}


void push_queue(int key)
{
	if(rear == N-1)
		printf("Queue Overflow\n");
	else
	{
		if(front == -1) 
			front = 0;
		rear = rear+1;
		queue[rear] = key ;
	}
}
 
int isEmpty_queue()
{
	if(front == -1 || front > rear)
		return 1;
	else
		return 0;
}
 
int pop_queue()
{
	int delete_item;
	if(front == -1 || front > rear)
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	
	delete_item = queue[front];
	front = front+1;
	return delete_item;
}