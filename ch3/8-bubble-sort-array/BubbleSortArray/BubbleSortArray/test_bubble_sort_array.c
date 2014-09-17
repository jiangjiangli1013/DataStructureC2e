#include "bubble_sort_array.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	ElementType array[5]={5,3,1,7,2};
	ElementType a=1, b=2;

	/* Test function 'swapElem' */
	printf("Test function 'swapElem'\n\n");
	printf("Before swapElem:\n");
	printf("a=%d, b=%d\n",a,b);
	swapElem(&a,&b);
	printf("After swapElem:\n");
	printf("a=%d, b=%d\n",a,b);
	printf("\n");

	/* Test function 'bubbleSortArray' */
	printf("Test function 'bubbleSortArray'\n\n");
	printf("Before bubbleSortArray:\n");
	printArray(array,5);
	bubbleSortArray(array,5);
	printf("After bubbleSortArray:\n");
	printArray(array,5);
	printf("\n");

	return 0;
}