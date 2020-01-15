// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
// Header file containing function declarations 
#include "pi.h"

int main(void)
{
// Float variables to store approximations from each function call
float forApprox, whileApprox;
forApprox = get_pi_for();
whileApprox = get_pi_while();
// Prints the approximations to the user
//printf("For loop approximation: %f\n", forApprox);
printf("While loop approximation: %f", whileApprox);
return 0;	
}