/*
 * Name: Michelle Chen
 * Title: Threads - Parallel matrix multiply (one thread per row)
 * Description: Computes C = A * B using N threads, where each thread computes
 *              one full row of C (A is NxM, B is MxL, C is NxL).
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

void *multiplyRow(void *arg) {
	int i = (int)(size_t)arg;
	int j, k;

	for (j = 0; j < L; j++) {
		double temp = 0;
		for (k = 0; k < M; k++)
			temp += A[i][k] * B[k][j];
		C[i][j] = temp;
	}
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	int i;

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

	pthread_t threads[N];

	for (i = 0; i < N; i++)
		pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i);

	for (i = 0; i < N; i++)
		pthread_join(threads[i], NULL);

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
