#include "stdlib.h"
#include "stdio.h"

float **matrix;
int x; //rows
int y; //lines

static inline void matrix_print(float **matrix)
{
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++)
			printf("%g\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main()
{
	// data input
	FILE * pFile;
	pFile = fopen ("./input.txt","r");
	if (pFile==NULL) return -1;
	fscanf (pFile,"%d%d",&x,&y);
	matrix = (float **)malloc(y*sizeof(float *));
	for(int i = 0; i<y; i++)
		matrix[i] = (float *)malloc(x*sizeof(float));
	for (int i = 0; i<x; i++)
		for (int j = 0; j<y; j++)
			fscanf(pFile,"%g",&matrix[i][j]);
	fclose (pFile);
	
	matrix_print(matrix);
	while (1) // iteration
	{
		// select min in lines
		float min = 0;
		int min_y = 1;
		for (int j = 1; j < y; j++)
			if (matrix[0][j] < min)
			{
				min = matrix[0][j];
				min_y = j;
			}
		printf("select column : %g at: %d \n",min,min_y);
		if (min == 0)break; // no nore iteration
		// select max in rows
		float max = 0;
		int max_x = 0;
		for (int i = 1; i < x; i++)
			if ( (matrix[i][min_y] > 0) && (matrix[i][min_y] / matrix[i][0] > max))
			{
				max = matrix[i][min_y] / matrix[i][0];
				max_x = i;
			}
		printf("select row : %g at: %d \n",max, max_x);
		matrix_print(matrix);
		// elementary row transformation 
		// row times 
		for (int n = 0; n < y; n++)
			matrix[max_x][n] *= 1 / matrix[max_x][min_y];
		//matrix_print(matrix);
		// row add 
		for (int i = 0; i < y; i++)
			if (i != max_x && matrix[i][min_y] != 0){
				float coff =-matrix[i][min_y];
				for (int n = 0; n < y; n++)
					matrix[i][n] = matrix[i][n]+ coff*matrix[max_x][n];
			}
		matrix_print(matrix);

	}
	// print solution
	matrix_print(matrix);
	printf("solution:\n");
	printf ("%g\t\n",matrix[0][0]);
	for (int i = 1; i < y; i++)
		if(matrix[0][i] == 0){
			for (int j = 0; j < x; j++)
				if (matrix[j][i] == 1)
				{
					printf("%g\t",matrix[j][0]);
					break;
				}
			}
		else
			printf("%g\t",0.0);
	for (int i = 0; i < y; i++)
	     free(matrix[i]);
	free(matrix);
	return 0;
}
