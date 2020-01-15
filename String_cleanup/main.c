// Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define TEST_STRING " \t a\n\nb \t c\n\t "
	
	
	
int main(void)
{
	char word[] = TEST_STRING;
	char word2[] = TEST_STRING;
	str_truncate(word);
	printf("%s\n\n", word); 
	str_delete_white(word2);
	printf("%s\n", word2);
	
return 0;	
}