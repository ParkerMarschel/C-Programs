#include <stdio.h>
// Header file for functions 
#include "pi.h"

float get_pi_for(void)
{
// Denominator number to be increased after each iteration 
int denom = 1;
float piApprox = 0.0;
int iter;
// Loop runs as many times as the constant variable LOOPS
for (iter = 0; iter < LOOPS; iter++)
{
	// Use if statement to alternate sign in equation 
	if ((iter % 2) == 0)
	{
		// Add new value to the approximation
		piApprox += (4.0/denom);
	}
	else
	{
		// Subtract new value from the approximation
		piApprox -= 4.0/denom;
		
	}
	// Add 2 to the dednominator for every iteration
	denom += 2;
}
// returns the approximation of PI
return piApprox;
}


float get_pi_while(void)
{
int run = 0;
// variables will be mutulated
float adjacents;
int flag = 1;
int denom = 1;
float piApprox = 0.0;
do
{
	// Reset the value back to 0.0
	adjacents = 0.0;
	printf("Run: %d\n", run);
	// If conditionals alternate the sign of the equation
	if (flag)
	{	
		// Checks the future adjacent pairs for THRESHOLD  comparison
		adjacents = (4.0/denom) - (4.0/(denom + 2));
		piApprox += 4.0/denom;
		// Swap the flag for 
		flag = 0;
	}
	// Else conditional used for subtracting values
	else
	{
		adjacents = (4.0/denom) + (4.0/(denom + 2));
		piApprox -= 4.0/denom;
		// Swap flag
		flag = 1;
	}
	// Add 2 for next denominator value
	denom += 2;
	run++;
} while (adjacents > THRESHOLD);
printf("Runs: %d\n", run);
// Returns the approximated PI value
return piApprox;
}





