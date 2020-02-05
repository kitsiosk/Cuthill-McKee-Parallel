#include "helper.h"
#define N 8

// Define queue as global variable
int queue[N], front = -1,rear = -1;
void push_queue(int key);
int pop_queue();
int isEmpty_queue();

void parallelSort(int values[], int keys[], int n);
void swap(int *xp, int *yp);
int findMinUnvisited(int *array, int *visited, int n);
int *RCM(int A[N][N]);
void print2D(int A[N][N]);


int main(){
    int A[N][N] = {
        {1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1}
    };
    

    printf("Initial Matrix: \n");
    print2D(A);

    int *R = (int *) malloc(N*sizeof(int));
    R = RCM(A);

    printf("Permutation Vector: \n");
    for(int i=0; i<N; ++i){
        printf("%d ", R[i]);
    }
    printf("\n\n");

    // Create the output matrix after the permutation
    int A_new[N][N];
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            A_new[i][j] = A[R[i]][R[j]];
        }
    }

    //Print Matrix after permutation
    printf("Matrix after permutations: \n");
    print2D(A_new);

    return 0;
}

int *RCM(int A[N][N]){
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
        for(int j=0; j<N; ++j){
            // If node j is adjacent to p
            if( A[p][j] == 1 && p!=j){
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

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
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

void print2D(int A[N][N]){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}