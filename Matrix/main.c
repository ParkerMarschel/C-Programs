// Preprocessor directives
#include <stdio.h>
#include "tt.h"

// Driver 
int main(void)
{
// 2-d array declaration 
int tt[10][10];
// Integer varaible declarations
int result, x, y;
// function calls
write_tt(tt);
read_tt(tt);
// Print statement prompts the user to enter a product
printf("Please enter a product i.e. 5*4: ");
// reads user input
scanf("%d*%d", &x, &y);
// Stores the result 
result = result_tt(tt, x, y);
// Prints the result to the screen
printf("%d * %d = %d\n\n\n", x, y, result);
printf("-------------------------------------------");
}