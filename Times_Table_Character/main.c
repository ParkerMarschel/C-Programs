// Preprocesor directives 
#include <stdio.h>
// Header file for function calls 
#include "tt.h"

/*
Main method calls each function and ask
the user to enter two numbers they want computed
The result is then printed back to the user on the screen
*/
int main(void)
{
int result, rows, columns;
write_tt();
read_tt();
printf("Please enter the product, e.g. 5*5: ");
scanf("%d*%d", &rows, &columns);
result = result_tt(rows, columns);
printf("Result: %d", result);
return 0;
}
