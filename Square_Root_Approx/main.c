// Preprocessor directives 
#include <stdio.h>
// Header file for function declarations
#include "square_root.h"

int main()
{
// Variable declarations 
float root;
float userNum;
// Loops iterates only when user enters a negative number
do
{
	// Prompts the user to enter a number
	printf("Enter positive number: ");
	// reads and stores imteger in variable
	scanf("%f", &userNum);
} while (userNum < 0);
// Prints the return result from the function call
printf("Square root is: %f\n", square_root(userNum));
return 0;
}
