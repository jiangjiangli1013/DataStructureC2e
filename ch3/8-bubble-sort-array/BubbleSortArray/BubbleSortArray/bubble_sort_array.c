#include "bubble_sort_array.h"

#include <stdio.h>

/* Swap two elements */
/* Note that we operate on pointers */
/* tmp=a; a=b; b=tmp; */
void swapElem(ElementType* a, ElementType* b)
{
	ElementType tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}

/* Bubble sort on a array */
/* Note that we operate on pointers */
void bubbleSortArray(ElementType *array, int length)
{
	int i, j;

	/* the last pass is not needed, so only 'length-1' pass */
	/* after every pass, a large value is bubbled to the last part of the array */ 
	for(i=0;i<length-1;i++)
	{
		/* the last 'i' elements are already sorted, so we sort 'length-i' elements */
		/* j, j+1, so we operate on index '0' to 'length-i-1' */
		for(j=0;j<length-i-1;j++)
		{
			if(array[j]>array[j+1])
			{
				swapElem(&array[j], &array[j+1]);
			}
		}
	}
}

/* print array */
void printArray(ElementType array[], int length)
{
	int i;
	
	for(i=0;i<length;i++)
	{
		printf("%d\n", array[i]);
	}
}