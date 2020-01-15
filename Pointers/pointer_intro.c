// Preprocessor directives
#include <stdio.h>
#include <stdlib.h> 
#include "pointer_intro.h"

// Driver
int main(void)
{
	// Declaration/Initializations
	int a = 3, b = 2, c = 1, point = 0, length, concatLen; 
	int *ptrA = &a;
	int *ptrB = &b; 
	int *ptrC = &c;
	char str1[] = "Pointers rock,";
	char str2[] = "once you get the hang of it!";
	char *concatinated = str_concat(str1, str2);
	
	// Prints results of function calls
	length = str_len(str1);
	length -= 1;
	printf("The length of the first string: %d\n", length);
	while(*(concatinated + point) != '\0')
	{
		printf("%c", *(concatinated + point));
		point++;
	}
	reorder(ptrA, ptrB, ptrC);
	return 0;	
}

// Calculates the length of a string 
int str_len(char* string_ptr)
{
	// Integer variable stores the length of the string
	int ltrCnt = 0;
	while(*string_ptr != '\0')
	{
		// Counts number of characters
		ltrCnt++;
		// move the pointer over 1 place at a time
		*string_ptr++;
	}
	// Return the length of the string
	return ltrCnt;
}

// Concatinates two strings together
char* str_concat(char* first_string, char* second_string)
{
	int place1 = 0, place2 = 0, length1, length2;
	// gets the length of both strings 
	length1 = str_len(first_string);
	length2 = str_len(second_string);	
	//Declare a new pointer with enough memory for both strings
	char* concatStr = (char*)malloc((length1 + length2 + 1) * sizeof(char));
	
	// iterates through the string
	while(*(first_string + place1) != '\0')
	{
		// Moves values over 
		*(concatStr + place1) = *(first_string + place1);
		place1++;
	}
	// Iterates through the string 
	while(*(second_string + place2) != '\0')
	{
		// move values over
		*(concatStr + place1) = *(second_string + place2);
		// update each positional value
		place2++;
		place1++;
	}
	// Put ending ascii character at the end
	*(concatStr + place1) = '\0';
	// return the concatinated pointer to a string 
	return concatStr;
}

// Reorders integers
void reorder(int* a, int* b, int* c)
{
	// Temp storage for swapping
	int temp = *a;
	// checks if they are in order and will run until they are
	while((*a > *b) || (*b > *c))
	{
		// First condition in while loop
		if(*a > *b)
		{
			// Swaps values
			temp = *a;
			*a = *b;
			*b = temp;
		}
		// Second condition in while loop
		else if(*b > *c)
		{
			// Swaps values
			temp = *b;
			*b = *c;
			*c = temp;
		}			
	}
	// Prints the numbers in order 
	printf("\nThe value of a is: %d\n", *a);
	printf("The value of b is: %d\n", *b);
	printf("The value of c is: %d\n", *c);
}

	