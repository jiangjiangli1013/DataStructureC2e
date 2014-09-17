#ifndef BUBBLE_SORT_ARRAY_H
#define BUBBLE_SORT_ARRAY_H

/* integer array */
typedef int ElementType;

/* Swap two elements */
void swapElem(ElementType* a, ElementType* b);
/* Bubble sort on a array */
void bubbleSortArray(ElementType *array, int length);
/* print array */
void printArray(ElementType array[], int length);

#endif /* BUBBLE_SORT_ARRAY_H */