#include "vld.h"

#include "cursor_list.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	/* Declarations */
	List list;
	List list_1;
	List list_2;
	List list_3;
	List list_4;
	List list_5;
	List list_6;
	Position pos;
	Position pos_1;
	Position pos_2;
	Position pos_3;
	Position pos_4;
	Position pos_a, pos_b;
	int len;
	int idx;
	ElementType elem;

	/* Initialize list */
	initializeCursorSpace();
	showMemoryAvailable();
	list=createList();

	/* Test functions 'insertNode' and 'appendNode' */
	printf("Test functions 'insertNode' and 'appendNode'\n\n");
	printf("Before 'insertNode':\n");
	printList(list);
	pos_1=getHeaderNode(list);
	insertNode(11, list, pos_1);
	pos_2=advanceNode(pos_1);
	insertNode(2, list, pos_2);
	pos_3=advanceNode(pos_2);
	insertNode(3, list, pos_3);
	pos_4=advanceNode(pos_3);
	insertNode(10, list, pos_4);
	insertNode(9, list, pos_2);
	printf("After 'insertNode':\n");
	printList(list);
	printf("Before 'appendNode':\n");
	printList(list);
	appendNode(7, list);
	appendNode(2, list);
	printf("After 'appendNode'\n");
	printList(list);
	printf("\n");

	/* Test functions 'cloneList', 'deleteNode' and 'deleteList' */
	printf("Test functions 'cloneList', 'deleteNode' and 'deleteList'\n\n");
	list_1=cloneList(list);
	printf("Before 'deleteNode':\n");
	printList(list_1);
	deleteNode(2, list_1);
	printf("After 'deleteNode':\n");
	printList(list_1);
	printf("Before 'DeleteList':\n");
	printList(list_1);
	deleteList(list_1);
	printf("After 'DeleteList':\n");
	printList(list_1);
	printf("\n");

	/* Test function 'getListLength' */
	printf("Test function 'getListLength'\n\n");
	len=getListLength(list);
	printf("Length: %d\n", len);
	printf("\n");

	/* Test functions 'findNode', 'findNodePrevious' and 'getNodeIndex' */
	printf("Test functions 'findNode', 'findNodePrevious' and 'getNodeIndex'\n\n");
	elem=2;
	pos=findNode(elem, list);
	if(pos!=NULL)
	{
		idx=getNodeIndex(pos, list);
		printList(list);
		printf("Finding %d, Element at index %d found\n", elem, idx);
	}
	else
	{
		printf("Finding %d, not found\n", elem);
	}
	elem=3;
	pos=findNodePrevious(elem, list);
	/* Check whether elem is found in list */
	if(CursorSpace[pos].m_next!=NULL)
	{
		idx=getNodeIndex(pos, list);
		printf("Finding previous element of %d, Element at index %d found\n", elem, idx);
	}
	else
	{
		/* elem is not in list */
		printf("Finding previous element of %d, but %d is not found\n", elem, elem);
	}
	printf("\n");

	/* Test functions 'makeListEmpty' and 'isListEmpty' */
	printf("Test functions 'makeListEmpty' and 'isListEmpty'\n\n");
	list_2=cloneList(list);
	printf("Before 'makeListEmpty':\n");
	printList(list_2);
	list_2=makeListEmpty(list_2);
	if(isListEmpty(list_2))
	{
		printf("List emptied successfully\n");
		printf("After 'makeListEmpty'\n");
		printList(list_2);
	}
	printf("\n");

	/* Test functions 'getHeaderNode', 'getFirstNode', 'getLastNode', 'advanceNode' and 'getNodeElem' */
	printf("Test functions 'getHeaderNode', 'getFirstNode', 'getLastNode', 'advanceNode' and 'getNodeElem'\n\n");
	printList(list);
	pos=getHeaderNode(list);
	printf("Header at index %d\n", getNodeIndex(pos, list));
	pos=getFirstNode(list);
	printf("First element at index %d have value %d\n", getNodeIndex(pos, list), getNodeElem(pos));
	pos=getLastNode(list);
	printf("Last element at index %d have value %d\n", getNodeIndex(pos, list), getNodeElem(pos));
	pos=getFirstNode(list);
	pos=advanceNode(pos);
	printf("Second element at index %d have value %d\n", getNodeIndex(pos, list), getNodeElem(pos));
	printf("\n");

	/* Test function 'reverseList' */
	printf("Test function 'reverseList'\n\n");
	list_3=cloneList(list);
	printf("Before 'reverseList':\n");
	printList(list_3);
	list_3=reverseList(list_3);
	printf("After 'reverseList':\n");
	printList(list_3);
	printf("\n");

	/* Test function 'swapNode' */
	printf("Test function 'swapNode'\n\n");
	list_4=cloneList(list);
	printf("Before 'swapNode':\n");
	printList(list_4);
	pos_a=getHeaderNode(list_4);
	pos_a=advanceNode(pos_a);
	pos_a=advanceNode(pos_a);
	pos_b=advanceNode(pos_a);
	swapNode(pos_a, pos_b, list_4);
	printf("After 'swapNode':\n");
	printList(list_4);
	printf("\n");

	/* Test function 'bubbleSortList' */
	printf("Test function 'bubbleSortList'\n\n");
	list_5=cloneList(list);
	printf("Before 'bubbleSortList':\n");
	printList(list_5);
	bubbleSortList(list_5);
	printf("After 'bubbleSortList':\n");
	printList(list_5);
	printf("\n");

	/* Test function 'connectList' */
	printf("Test function 'connectList'\n\n");
	printf("List 1:\n");
	printList(list);
	printf("Length: %d\n", getListLength(list));
	printf("List 2:\n");
	printList(list_5);
	printf("Length: %d\n", getListLength(list_5));
	list_6=connectList(list, list_5);
	printf("Connected list:\n");
	printList(list_6);
	printf("Length: %d\n", getListLength(list_6));
	printf("\n");

	/* Cleanup memory */
	destroyList(list);
	destroyList(list_1);
	destroyList(list_2);
	destroyList(list_3);
	destroyList(list_4);
	destroyList(list_5);
	destroyList(list_6);
	showMemoryAvailable();

	return 0;
}