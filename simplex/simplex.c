#include "stdlib.h"
#include "stdio.h"

float **matrix;
int x; //rows
int y; //lines

static inline void matrix_print()
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
	matrix = (float **)malloc((x)*sizeof(float *));
	for(int i = 0; i<x; i++)
		matrix[i] = (float *)malloc((y)*sizeof(float));
	for (int i = 0; i<x; i++)
		for (int j = 0; j<y; j++)
			fscanf(pFile,"%g",&matrix[i][j]);
	matrix_print();
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
		printf("select column: %g at: %d \n",min,min_y);
		if (min == 0) break; // no nore iteration, =0 for clearity, use min-0 <eps may be better
		// select max in rows
		float max = 0;
		int max_x = 0;
		for (int i = 1; i < x; i++)
			if ( (matrix[i][min_y] > 0) && (matrix[i][min_y] / matrix[i][0] > max))
			{
				max = matrix[i][min_y] / matrix[i][0];
				max_x = i;
			}
		if (max == 0 ){
			printf("no solution\n");
			fclose (pFile);
			free(matrix);
		};
		printf("select row : %g at: %d \n",max, max_x);
		
		// elementary row transformation 
		// row times 

		float coff = matrix[max_x][min_y];
		for (int n = 0; n < y; n++)
			matrix[max_x][n] /= coff;
		// row add 
		for (int i = 0; i < x; i++)
			if (i != max_x && matrix[i][min_y] != 0){
				float coff =-matrix[i][min_y];
				for (int n = 0; n < y; n++)
					matrix[i][n] = matrix[i][n]+ coff*matrix[max_x][n];
			}
		matrix_print();

	}
	// print solution
	matrix_print();
	printf ("solution:\n%g\t\n",matrix[0][0]);
	fclose (pFile);
	free(matrix);
	return 0;
}
