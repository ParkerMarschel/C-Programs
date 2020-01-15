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

char arr[10];
// Variable declarations for loops 
int row, columns, num;
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
		num = row * columns;
		// Read from the file and store the value
		sprintf(arr, "%4d", num);
		// Print the value to the screen
		fwrite(arr, 1, sizeof(arr), handle);
	}
	fwrite("\n", 1, sizeof(char), handle);
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
int row, columns, value;
// Create the file handle
FILE* times_table;
// Opens up the file for reading
times_table = fopen(DATA_FILE, "r");
// If there is nothing written in the file 
if (times_table == NULL)
{
	// Error message displayed back to the user 
	printf("Opening file %s failed\n", DATA_FILE);
	return;
}
//Nested loops form the times table 
		// Reads from 1 element at a time and stores in the buffer array
while(fread(&value, sizeof(int), 1, times_table) != 0);
{
		// Will print the first value in the buffer array
		printf("%d", value);	
}
	// Next row of values will be on a new value
fclose(times_table);
}
// Function calculates the result 
int result_tt(int x, int y)
{
char buffer[500];
// Create the file handle
FILE *times_table;
// open the file for reading
times_table = fopen(DATA_FILE, "r");
int result, offset, iter = 0;
//offset = (x-1) * 10 + y - 1;
// Equation to find how many elements need to be read to obtain the number
int readTo = (10 * (x - 1)) + y;
printf("Read to is: %d", readTo);
// Checks if the file handle will not open
if (times_table == NULL)
{
	// Prints an error message to the screen
	printf("Opening file %s failed\n", DATA_FILE);
	return -1;
}

fseek(times_table, readTo*sizeof(int), SEEK_SET); 
while(sizeof(iter) < readTo)
{	
	// Read through the file and store number for each iteration
	fread(&result, sizeof(buffer), 1, times_table);
	// Increment the counter
	iter++;	
}
// Close the file 
fclose(times_table);
// Return the integer result of function
return result;
}