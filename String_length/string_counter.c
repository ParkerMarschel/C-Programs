#include <stdio.h>
#include <stdlib.h>
#include "string_counter.h"

int str_len(char string[]){
	/*
	// variable counts the number of non-letters
	int nonChar = 0;
	int i;
	for(i = 0; string[i] != '\0'; i++){
		if(string[i] == '\n' || string[i] == ' '){
			nonChar++;
		}
	}
	return i - nonChar;
	*/
	
	// variable counts the number of non-letters
	int nonChar = 0;
	int i = 0;
	for(; string[i++] != '\0';){
		if(string[i] == '\n' || string[i] == ' '){
			nonChar++;
		}
	}
	return i - (nonChar + 1);
	
	/*
	// variable counts the number of non-letters
	int nonChar = 0;
	int i = 0;
	while(string[i] != '\0'){
		if(string[i] == '\n' || string[i] == ' '){
			nonChar++;
		}
		i++;
	}
	return i - nonChar;
	*/
	/*
	// variable counts the number of non-letters
	int nonChar = 0;
	int i = 0;
	while(string[i++] != '\0'){
		if(string[i] == '\n' || string[i] == ' '){
			printf("%d\n", i);
			nonChar++;
		}
	}
	return i - (nonChar + 1);
	*/
}
