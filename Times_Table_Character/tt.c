// Preprocessor directives 
#include <stdio.h>
#include <stdlib.h>
// Header file for functions
#include "tt.h"

// Define a file constant
#define DATA_FILE "times_table.txt"

// Function 
void write_tt(void)
{
// Variable declarations for loops 
int row, columns;
// File handle declaration
FILE* handle;
// File is opened to write to 
handle = fopen(DATA_FILE, "w");
// Ckecks if the file could not be opened
if (handle == NULL)
{
	// Error message is displayed back to the user
	printf("Opening file %s failed\n");
	return;	
}
// Nested loops write the times table to the file 
for(row = 1; row <= 10; row++)
{
	for(columns = 1; columns <= 10; columns++)
	{
		fprintf(handle, "%4d", row * columns);
	}
}
// Close the file
fclose(handle);
}

/*
Method reads from the file and displays
the times table back to the user
*/
void read_tt(void)
{
// Integer variable declarations 
int row, columns, num;
// Create the file handle
FILE* times_table;
// Opens up the ifile for reading
times_table = fopen(DATA_FILE, "r");
// If there is nothing written in the file 
if (times_table == NULL)
{
	// Error message displayed back to the user 
	printf("Opening file %s failed\n", DATA_FILE);
	return;
}
//Nested loops form the times table 
for(row = 1; row <= 10; row++)
{
	for(columns = 1; columns <= 10; columns++)
	{
		// Read from the file and store the value
		fscanf(times_table, "%d", &num);
		// Print the value to the screen
		printf("%d\t", num);
	}
	// Next row of values will be on a new value
printf("\n"); 
}
}

// Function calculates the result 
int result_tt(int x, int y)
{
// Create the file handle
FILE *times_table;
// open the file for reading
times_table = fopen(DATA_FILE, "r");
int result, offset, iter = 0;
// Equation to find how many elements need to be read to obtain the number
int readTo = (10 * (x - 1)) + y;
// Checks if the file handle will not open
if (times_table == NULL)
{
	// Prints an error message to the screen
	printf("Opening file %s failed\n", DATA_FILE);
	return -1;
}
// While loop iterates up to the number needed
while(iter < readTo)
{	
	// Read through the file and store number for each iteration
	fscanf(times_table, "%d", &result);
	// Increment the counter
	iter++;	
}
// Close the file 
fclose(times_table);
// Return the integer result of function
return result;
}