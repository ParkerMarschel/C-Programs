// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include "tt.h"

void write_tt(int tt[][10])
{
	int rows, columns, value;
	// Nested for loops decrement by 1
	for (rows = 10; rows >= 1; rows--)
	{
		for (columns = 10; columns >= 1; columns--)
		{
			// Calulates new value for each iteration
			value = rows*columns;
			// Places the value at the proper indice
			tt[rows - 1][columns - 1] = value;
		}
	}
}

// Function reads the matrix and prints it to the screen
void read_tt(int tt[][10])
{
	// Variable declarations
	int value, row, column;
	printf("\ntt initialized ...\n\n");
	// Nested loops iterate through the matrix
	for (row = 10; row >= 1; row--)
	{
		for (column = 10; column >= 1; column--)
		{
			// Prints the value at the current indices out
			printf("%d\t", tt[row - 1][column - 1]);
		}
	// Prints a newline character for each new row	
	printf("\n");
	}
}

// Function finds result and returns it as an integer
int result_tt(int tt[][10], int x, int y)
{
	int product;
	// stores the element at the indice 
	product = tt[x - 1][y - 1];
	// Returns the product
	return product;
}
