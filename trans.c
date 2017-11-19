/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose (int M, int N, int A[N][M], int B[M][N]);

void transpose_submit32 (int M, int N, int A[N][M], int B[M][N]);
void transpose_submit64 (int M, int N, int A[N][M], int B[M][N]);
void transpose_submit61 (int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit (int M, int N, int A[N][M], int B[M][N])
{
	if (M == 32) transpose_submit32(M, N, A, B);
	if (M == 64) transpose_submit64(M, N, A, B);
	if (M == 61) transpose_submit61(M, N, A, B);
}


void transpose_submit32 (int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l, temp;
	int block = 8;
	int block2 = 8;

	for (i = 0; i < N / block + 1; i++) {
		for (j = 0; j < M / block2 + 1; j++) {
			for (k = 0; k < block; k++) {
				if (block * i + k == N) break;
				for (l = 0; l < block2; l++) {
					if (block2 * j + l == M) break;
					if (block * i + k == block2 * j + l) {
						temp = A[block * i + k][block2 * j + l];
					} else
						B[block2 * j + l][block * i + k] = A[block * i + k][block2 * j + l];

				}
				if (i == j)
					B[block * i + k][block * i + k] = temp;
			}
		}
	}
}


void transpose_submit64 (int M, int N, int A[N][M], int B[M][N])
{
	int i = 0, j = 0, k =  0;
	int temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;
	for (j = 0; j < N; j += 8) {
		for (i = 0; i < M; i += 8) {
			for (k = 0; k < 8; k++) {
				temp1 = A[i + k][j];
				temp2 = A[i + k][j + 1];
				temp3 = A[i + k][j + 2];
				temp4 = A[i + k][j + 3];
				if (k == 0) {
					temp5 = A[i + k][j + 4];
					temp6 = A[i + k][j + 5];
					temp7 = A[i + k][j + 6];
					temp8 = A[i + k][j + 7];
				}
				if (k == 7) {
					temp9 = A[i + k][j + 6];
				}
				B[j][i + k] = temp1;
				B[j + 1][i + k] = temp2;
				B[j + 2][i + k] = temp3;
				B[j + 3][i + k] = temp4;


			}
			for (k = 7; k > 0; k--) {
				temp1 = A[i + k][j + 4];
				temp2 = A[i + k][j + 5];
				if (k != 7)
					temp3 = A[i + k][j + 6];
				temp4 = A[i + k][j + 7];
				B[j + 4][i + k] = temp1;
				B[j + 5][i + k] = temp2;
				if (k != 7)
					B[j + 6][i + k] = temp3;
				B[j + 7][i + k] = temp4;
			}
			B[j + 4][i] = temp5;
			B[j + 5][i] = temp6;
			B[j + 6][i] = temp7;
			B[j + 7][i] = temp8;
			B[j + 6][i + 7] = temp9;
		}
	}

}

void transpose_submit61 (int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l, temp;
	int block = 20;
	int block2 = 20;

	for (i = 0; i < N / block + 1; i++) {
		for (j = 0; j < M / block2 + 1; j++) {
			for (k = 0; k < block; k++) {
				if (block * i + k == N) break;
				for (l = 0; l < block2; l++) {
					if (block2 * j + l == M) break;
					if (block * i + k == block2 * j + l) {
						temp = A[block * i + k][block2 * j + l];
					} else
						B[block2 * j + l][block * i + k] = A[block * i + k][block2 * j + l];

				}
				if (i == j)
					B[block * i + k][block * i + k] = temp;
			}
		}
	}
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans (int M, int N, int A[N][M], int B[M][N])
{
	int i, j, tmp;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			tmp = A[i][j];
			B[j][i] = tmp;
		}
	}

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions ()
{
	/* Register your solution function */
	registerTransFunction(transpose_submit, transpose_submit_desc);

	/* Register any additional transpose functions */
	registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose (int M, int N, int A[N][M], int B[M][N])
{
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; ++j) {
			if (A[i][j] != B[j][i]) {
				return 0;
			}
		}
	}
	return 1;
}
