#include <stdio.h>
#include <stdlib.h>


// Function declarations
float add(float first, float second);
float subtract(float first, float second);
float multiply(float first, float second);
float divide(float first, float second);

int main(int argc, char* argv[])
{
	float first, second, ans;
	// Get user input from command line using sscanf
	sscanf(argv[1], "%f", &first);
	sscanf(argv[2], "%f", &second);
	// Pointer array 
	float (*ptr[])(float, float) = {add, subtract, multiply, divide, NULL};
	int index = 0;
	// Indexes through the pointer array and calls each function
	while(*ptr[index] != NULL)
	{
		ans = (*ptr[index])(first, second);
		printf("%f\n", ans);
		// Increment for the condition 
		index++;
	}
return 0;
}

// fucntion adds values 
float add(float first, float second)
{
	printf("%f + %f is: ", first, second);
	// returns the addition of floats
	return first + second;
}


// function subtracts values
float subtract(float first, float second)
{
	printf("%f - %f is: ", first, second);
	return first - second;
}

//function multiplies values
float multiply(float first, float second)
{
	printf("%f * %f is: ", first, second);
	return first * second;
}


//function divides values
float divide(float first, float second)
{
	printf("%f/%f is: ", first, second);
	return first/second;
}

