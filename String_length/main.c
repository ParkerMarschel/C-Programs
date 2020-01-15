// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>

// Function declarations
int str_len(char string[]);

//Driver 
int main(void){
char str[500];
printf("Please enter a string: ");
fgets(str, sizeof str, stdin);
printf("string is: %s\n", str);
printf("The length of the string is: %d\n", str_len(str));
return 0;	
}

// Function finds the length of the string entered by the user
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
