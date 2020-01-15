#include "square_root.h"

// Function calculates the new approximation value and returns it as a float
float square_root_aux(float number, float approx)
{
// Calculates the new sqaure root approximation using approximation algorithm
float newApprox = approx + ((number - (approx * approx))/(2*approx));
// Return the new approximation value

return newApprox;	
}

float square_root(float number)
{
// Set new to one for the first iteration through 
float old;
float new = 1.0;
do
{
	// Set old to new value to save it for comparison in while loop
	old = new;
	// New value is the value of the new approximation
	new = square_root_aux(number, old);
} while ((old - new) != 0);
return new;	
}