#include <stdio.h>

void printArray (int N, int M, int A[N][M]);
void copy_transpose_4_4 (int i_xoffset, int i_yoffset,
                         int d_xoffset, int d_yoffset, int M, int N, int A[N][M], int B[M][N]);

int main (){
	int N = 8;
	int M = 8;

	int test[64][64] = {0};
	int i = 0;
	for (int k = 0; k < 64; k++) {
		for (int l = 0; l < 64; l++) {
			test[l][k] = i;
			i++;
		}
	}

	printArray(64, 64, test);


  int buffer[8][8]={0};

	int new[64][64] = {0};
  /*copy_transpose_4_4(0,0,0,0,  M, N, test, buffer);
  copy_transpose_4_4(4, 0, 4, 0, M, N, test, buffer);
  copy_transpose_4_4(4, 4, 4,4, M, N, test, new);
  copy_original_4_4( 4,0,0, 4, M, N, buffer, new);
  copy_transpose_4_4(0, 4, 4, 0, M, N, test, buffer);
  copy_original_4_4(0, 0, 0, 0, M, N, buffer, new);
  copy_original_4_4( 4, 0, 4, 0, M, N, buffer, new);*/

  transpose_submit64(64,64,test,new);

  printArray(64, 64, new);


}

void transpose_submit64 (int M, int N, int A[N][M], int B[M][N])
{
	int i, j, buffer_x, buffer_y;

	for (i = 0; i < 7; i++) {
		j = i;
		buffer_x = 8 * (i + 1);
		buffer_y = 8 * (i + 1);
		copy_transpose_4_4(8 * i, 8 * j, buffer_x, buffer_y, M, N, A, B);
		copy_transpose_4_4(8 * i + 4, 8 * j, buffer_x + 4, buffer_y, M, N, A, B);
		copy_transpose_4_4(8 * i + 4, 8 * j + 4, 8 * j + 4, 8 * i + 4, M, N, A, B);
		copy_original_4_4(buffer_x + 4, buffer_y, 8 * j, 8 * i + 4, M, N, B, B);
		copy_transpose_4_4(8 * i, 8 * j + 4, buffer_x + 4, buffer_y, M, N, A, B);
		copy_original_4_4(buffer_x, buffer_y, 8 * j, 8 * i, M, N, B, B);
		copy_original_4_4(buffer_x + 4, buffer_y, 8 * j + 4, 8 * i, M, N, B, B);
	}
  printf("1endendendyeaheyeaeh\n");
  printArray(64, 64, B);
	{
    i=7;
    j=7;
		buffer_x = 8;
		buffer_y = 0;
		copy_transpose_4_4(8 * i, 8 * j, buffer_x, buffer_y, M, N, A, B);
		copy_transpose_4_4(8 * i + 4, 8 * j, buffer_x + 4, buffer_y, M, N, A, B);
		copy_transpose_4_4(8 * i + 4, 8 * j + 4, 8 * j + 4, 8 * i + 4, M, N, A, B);
		copy_original_4_4(buffer_x + 4, buffer_y, 8 * j, 8 * i + 4, M, N, B, B);
		copy_transpose_4_4(8 * i, 8 * j + 4, buffer_x + 4, buffer_y, M, N, A, B);
		copy_original_4_4(buffer_x, buffer_y, 8 * j, 8 * i, M, N, B, B);
		copy_original_4_4(buffer_x + 4, buffer_y, 8 * j + 4, 8 * i, M, N, B, B);
	}
  printf("2endendendyeaheyeaeh\n");
  printArray(64, 64, B);

	buffer_x = 56;
	buffer_y = 48;

	for (j = 0; j < 7; j++) {
		for (i = j + 1; i < 8; i++) {
			copy_transpose_4_4(8 * i, 8 * j, buffer_x, buffer_y, M, N, A, B);
			copy_transpose_4_4(8 * i + 4, 8 * j, buffer_x + 4, buffer_y, M, N, A, B);
			copy_transpose_4_4(8 * i + 4, 8 * j + 4, 8 * j + 4, 8 * i + 4, M, N, A, B);
			copy_original_4_4(buffer_x + 4, buffer_y, 8 * j, 8 * i + 4, M, N, B, B);
			copy_transpose_4_4(8 * i, 8 * j + 4, buffer_x + 4, buffer_y, M, N, A, B);
			copy_original_4_4(buffer_x, buffer_y, 8 * j, 8 * i, M, N, B, B);
			copy_original_4_4(buffer_x + 4, buffer_y, 8 * j + 4, 8 * i, M, N, B, B);

		}
	}
  printf("3endendendyeaheyeaeh\n");
  printArray(64, 64, B);
	buffer_x = 0;
	buffer_y = 8;

	for (j = 7; j >= 1; j--) {
		for (i = j - 1; i >= 0; i--) {
			copy_transpose_4_4(8 * i, 8 * j, buffer_x, buffer_y, M, N, A, B);
			copy_transpose_4_4(8 * i + 4, 8 * j, buffer_x + 4, buffer_y, M, N, A, B);
			copy_transpose_4_4(8 * i + 4, 8 * j + 4, 8 * j + 4, 8 * i + 4, M, N, A, B);
			copy_original_4_4(buffer_x + 4, buffer_y, 8 * j, 8 * i + 4, M, N, B, B);
			copy_transpose_4_4(8 * i, 8 * j + 4, buffer_x + 4, buffer_y, M, N, A, B);
			copy_original_4_4(buffer_x, buffer_y, 8 * j, 8 * i, M, N, B, B);
			copy_original_4_4(buffer_x + 4, buffer_y, 8 * j + 4, 8 * i, M, N, B, B);
		}
	}
  printf("4endendendyeaheyeaeh\n");
  printArray(64, 64, B);

	i = 1;
	j = 0;

	copy_transpose_4_4(8 * i, 8 * j, 8 * j, 8 * i, M, N, A, B);
	copy_transpose_4_4(8 * i + 4, 8 * j, 8 * j, 8 * i + 4, M, N, A, B);
	copy_transpose_4_4(8 * i, 8 * j + 4, 8 * j + 4, 8 * i, M, N, A, B);
	copy_transpose_4_4(8 * i + 4, 8 * j + 4, 8 * j + 4, 8 * i + 4, M, N, A, B);

  printf("5endendendyeaheyeaeh\n");
}

void printArray (int N, int M, int A[N][M]){
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			printf("%4d ", A[i][j]);
		}
		printf("\n");
	}
}

void copy_original_4_4 (int i_xoffset, int i_yoffset,
                        int d_xoffset, int d_yoffset, int M, int N, int A[N][M], int B[M][N]){
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			B[d_xoffset + x][d_yoffset + y] = A[i_xoffset + x][i_yoffset + y];
		}
	}
}

void copy_transpose_4_4 (int i_xoffset, int i_yoffset,
                         int d_xoffset, int d_yoffset, int M, int N, int A[N][M], int B[M][N]){
	int x, y;
	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			B[d_xoffset + y][d_yoffset + x] = A[i_xoffset + x][i_yoffset + y];
		}
	}
}
