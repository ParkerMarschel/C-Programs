// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>

//Function Declarations
void print_numbers(int my_numbers[], int dim);
void change_numbers(int my_numbers[], int dim);

// Main method calls both function
int main(void)
{
// Array for passing to parameter
int sampleArr[] = {1, 2, 3, 4, 5};
//Call print_numbers() first
print_numbers(sampleArr, 5);
// Change the numbers in the array
change_numbers(sampleArr, 5);
printf("\n");
// Print out the new values
print_numbers(sampleArr, 5);
return 0;
}

// Function prints out values in array
void print_numbers(int my_numbers[], int dim)
{
int index;
// For loop prints the values of the array
for(index = 0; index < dim; index++)
{
  // Prints the values of the array
  printf("%d ", my_numbers[index]);
}
}

// Function changes the vlues in the array
void change_numbers(int my_numbers[], int dim)
{
int newVal[] = {99, 98, 97, 96, 95};
int index;
// For loop puts numbers into the array
for (index = 0; index < dim; index++)
{
  // Stores the new value in place of the old
  my_numbers[index] = newVal[index];
}
}
