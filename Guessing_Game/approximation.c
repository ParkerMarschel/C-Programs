#include <stdio.h>
#include <stdlib.h>

// define constant variable for the max number
#define MAX 1000

//Function declaration
int approxNum();

// Main function prints the result
int main()
{
// stores the result of function call in variable
int foundNum = approxNum();
printf("Your number is: %d\n", foundNum);
return 0;
}

// Approximates the user number 
int approxNum()
{
/*
Declaration and initialization of variables to be used
*/
// Keeps count of the number of iterations through the loop
int count = 1;
// declaration of the user response
char response;
int max, mid, min;
max = MAX;
min = 0;
mid = (min + max) / 2;
// Loop iterates until the mid and the min are the same 
while(mid != max)
{
	/*
	do while loop prompts the user to enter a character and will continue
	to do so until they enter either a 'y' or 'n' and uses getchar() twice to store
	the result and get rid of the "\n" after enter is pushed by the user
	*/
	do
	{
		printf("%d. Is your number greater than %d? (y/n) ", count, mid);
		response = getchar();
		getchar();
	} while(response != 'y' && response != 'n');
	// Checks if the user's number is greater than the mid	
	if (response == 'y')
	{
		// Set min to the mid
		min = mid + 1;
		// Mid number equation
		mid = (min + max) / 2;
	}
	// Else conditional handles the user number being less than the mid
	else
	{
		// Set max to the mid
		max = mid;
		// Mid number equation
		mid = (min + max) / 2;
	}
	// Add to the count for the print statement to use
	count++;
}
// Returns the max which is the same number that the user entered
return max;
}
