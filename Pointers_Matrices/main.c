//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

// Driver
int main(void)
{
	// Variable declarion
	int rows, columns, offset = 0;
	float *resultMatr;
	float left[2][3] = {{1,2,3},{4,5,6}};
	float right[3][4] = {{7,8,9,10},{11,12,13,14},{15,16,17,18}};
	resultMatr = matrix_multiplication((float*)left, (float*)right, 2, 3, 4);
	
	for(rows = 0; rows < 2; rows++)
	{
		for(columns = 0; columns < 4; columns++)
		{
			printf("%f\t", *((resultMatr + (rows * offset)) + columns));
		}
		// Sets the offset to get the valules in row 2
		offset = 4;
		// Prints a new line for the second row
		printf("\n");
	}
return 0;	
}

// Function multiplies matrices using pointers
float* matrix_multiplication(float* left, float* right, int rows, int shared, int columns)
{
	// Offsets
	int rowsIndex, columnsIndex, sharedIndex;
	// Allocate proper space for the pointer to the result matrix
	float* resMatrix = (float*)malloc(rows * columns * sizeof(float));
	
	// Iterate through the rows
	for(rowsIndex = 0; rowsIndex < rows; rowsIndex++)
	{
		// Stores the sum of the multiplies
		float sum = 0;
		// Iterate throught the columns
		for(columnsIndex = 0; columnsIndex < columns; columnsIndex++)
		{
			// Resets the sum after each column is iterated
			sum = 0;
			// Iterate through shared to get values from both matrices
			for(sharedIndex = 0; sharedIndex < shared; sharedIndex++)
			{
				// Add the new value calculated each iteration to the sum
				sum += *(left + (rowsIndex * shared) + sharedIndex) * *(right + (sharedIndex * columns) + columnsIndex);
			}
			// Stores the sum into the return matrix 
			*(resMatrix + (rowsIndex * columns) + columnsIndex) = sum;
		}
	}
	// Returns a pointer to the resulting matrix
	return resMatrix;
}