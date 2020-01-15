#include <stdio.h>
#include <stdlib.h>
#include "swap_half.h"

// Function swaps half of a string
void swap_half(char* string)
{
	// Counts the length of the string
	int hIndex, leadIndex, tailIndex, cnt = 0, front = 0, strCnt = 0;
	char temp;
	printf("Before swap the string is: ");
	// Counts the length of the string
	while(*(string + strCnt) != '\0')
	{
		printf("%c", *(string + strCnt));
		strCnt++;
	}
	// Finds the half index of the string 
	hIndex = strCnt / 2;

	while(hIndex < strCnt)
	{
	// Swaps
		tailIndex = hIndex;
		leadIndex = hIndex - 1;
		while(leadIndex >= front)
		{
			temp = *(string + leadIndex);
			*(string + leadIndex) = *(string + tailIndex);
			*(string + tailIndex) = temp;
			// Decrements as it get towardsd the beginning of string
			tailIndex--;
			leadIndex--;
		}
		// Increments
		front++;
		hIndex++;
	}
	// Loop prints the swapped string
	printf("\nAfter the swap: ");
	while(cnt < strCnt)
	{
		printf("%c", *(string + cnt));
		cnt++;
	}
	printf("\n");
}

//Function mirrors a selected part of a string
void mirror(char* string, int from, int to)
{
	// Finds the length of the string passed in
	int strCnt = 0, printCnt = 0;
	char temp;
	// Prints the string before the mirror
	printf("\nString before mirroring: ");
		while(*(string + strCnt) != '\0')
	{
		printf("%c", *(string + strCnt));
		strCnt++;
	}
	
	// Mirrors the selected part of the string 
	while(from < to)
	{
		temp = *(string + from);
		*(string + from) = *(string + to);
		*(string + to) = temp;
		from++;
		to--;
	}
	
	//Prints the string after the mirror
	printf("\nString after mirroring: ");
	while(printCnt < strCnt)
	{
		printf("%c", *(string + printCnt));
		printCnt++;
	}
	printf("\n");
}