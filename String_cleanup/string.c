// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

void str_truncate(char* string)
{
	int index = 0, bIndex = 0, eIndex = 0, rIndex = 0, flag = 1;
	// Will run until the pointer is at the end of the string 
	while(flag)
	{
		// Checks for the fist valid character
		if(*(string + index) >= 33 && *(string + index) <= 126)
		{
			bIndex = index;
			flag = 0;
		}
		// Increment offset
		index++;	
	}
	
	// moves index to the end of the string
	while(*(string + rIndex) != '\0')
	{
		rIndex++;
	}
	
	// Finds the index value of last character in the string 
	while(rIndex > 0)
	{
		if(*(string + rIndex) >= 33 && *(string + rIndex) <= 126)
		{
			// Stores the end index ofthe string
			eIndex = rIndex;
			// Ends the loop
			rIndex = -1;
		}
		rIndex--;
	}
	// reset index value
	index = 0;
	// Loops through the actual string
	while(bIndex <= eIndex)
	{
		// Points at new value
		*(string + index) = *(string + bIndex);
		// Increment offsets
		index++;
		bIndex++;
	}
	// Mark the end of the string
	*(string + index) = '\0';
}

// Function deltes white spaces
void str_delete_white(char* string)
{
	int index = 0, bIndex = 0, eIndex = 0, rIndex = 0, flag = 1;
	// Will run until the pointer is at the end of the string 
	while(flag)
	{
		// Checks for the fist valid character
		if(*(string + index) >= 33 && *(string + index) <= 126)
		{
			bIndex = index;
			flag = 0;
		}
		index++;	
	}
	
	// moves index to the end of the string
	while(*(string + rIndex) != '\0')
	{
		rIndex++;
	}
	
	// Finds the index value of last character in the string 
	while(rIndex > 0)
	{
		if(*(string + rIndex) >= 33 && *(string + rIndex) <= 126)
		{
			// Stores the end index ofthe string
			eIndex = rIndex;
			// Ends the loop
			rIndex = -1;
		}
		rIndex--;
	}
	// Reset index value
	index = 0;
	// Loops through the actual string
	while(bIndex <= eIndex)
	{
		// Checks if pointing at a valid character
		if(*(string + bIndex) >= 33 && *(string + bIndex) <= 126)
		{
			// Points to correct value
			*(string + index) = *(string + bIndex);
			// Increment offset
			index++;
		}
		// Increment the offset
		bIndex++;
	}
	// Mark the end of the string
	*(string + index) = '\0';
	
}
