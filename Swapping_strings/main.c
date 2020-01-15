#include <stdio.h>
#include <stdlib.h>
#include "swap_half.h"

int main(void)
{
	char word1[] = "whatever";
	char word2[] = "EE222";
	swap_half(word1);
	printf("\n");
	swap_half(word2);
	printf("\n");
	mirror(word1, 0, 7);
	mirror(word2, 0, 4);
return 0;
}