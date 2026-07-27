/*
 * Name: Michelle Chen
 * Title: Threads - Parallel matrix multiply (one thread per element)
 * Description: Finer-grained version of matmul_row: computes C = A * B using
 *              N*L threads, where each thread computes one element of C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int N, M, L;
double **A, **B, **C;

double **allocMatrix(int r, int c) {
	int i;
	double **m = (double **)malloc(r * sizeof(double *));
	for (i = 0; i < r; i++)
		m[i] = (double *)malloc(c * sizeof(double));
	return m;
}

void initMatrix(int r, int c, double **m) {
	int i, j;
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			m[i][j] = rand() % 11;
}

void printMatrix(int r, int c, double **m) {
	int i, j;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++)
			printf("%6.1f ", m[i][j]);
		printf("\n");
	}
}

void *multiplyElement(void *arg) {
	int t = (int)(size_t)arg;
	int i = t / L;
	int j = t % L;
	int k;

	double temp = 0;
	for (k = 0; k < M; k++)
		temp += A[i][k] * B[k][j];

	C[i][j] = temp;
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	int t;
	int total;

	if (argc != 4) {
		printf("Usage: %s N M L\n", argv[0]);
		return 1;
	}

	N = atoi(argv[1]);
	M = atoi(argv[2]);
	L = atoi(argv[3]);

	srand(1);

	A = allocMatrix(N, M);
	B = allocMatrix(M, L);
	C = allocMatrix(N, L);

	initMatrix(N, M, A);
	initMatrix(M, L, B);

	total = N * L;
	pthread_t threads[total];

	for (t = 0; t < total; t++)
		pthread_create(&threads[t], NULL, multiplyElement, (void *)(size_t)t);

	for (t = 0; t < total; t++)
		pthread_join(threads[t], NULL);

	if (N <= 10 && M <= 10 && L <= 10) {
		printf("Matrix A (N x M):\n");
		printMatrix(N, M, A);
		printf("Matrix B (M x L):\n");
		printMatrix(M, L, B);
		printf("Matrix C (N x L):\n");
		printMatrix(N, L, C);
	} else {
		printf("Computed C of size %d x %d\n", N, L);
	}
	return 0;
}
