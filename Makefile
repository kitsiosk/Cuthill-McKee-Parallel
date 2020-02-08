CC = gcc
CFLAGS = -fopenmp

sequential: sequential.c
	$(CC) $(CFLAGS) sequential.c -o sequential.out

openmp: openmp.c
	$(CC) $(CFLAGS) openmp.c -o openmp.out

clean: 
	rm *.out