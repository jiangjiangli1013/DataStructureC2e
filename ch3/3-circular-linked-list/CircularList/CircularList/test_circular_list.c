#include "vld.h"

#include "circular_list.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	/* Declarations */
	CircularList list;
	CircularList list_1;
	CircularList list_2;
	CircularList list_3;
	Position pos;
	Position pos_1;
	Position pos_2;
	Position pos_3;
	Position pos_4;
	int len;
	int idx;
	ElementType elem;

	/* Initialize list */
	list=createList();

	/* Test functions 'insertNode' and 'appendNode' */
	printf("Test functions 'insertNode' and 'appendNode'\n\n");
	printf("Before 'insertNode':\n");
	printList(list);
	/* Initialize the first node */
	list->m_elem=1;
	pos_1=list;
	pos_2=advanceNode(pos_1);
	insertNode(2, list, pos_2);
	pos_3=advanceNode(pos_2);
	insertNode(3, list, pos_3);
	pos_4=advanceNode(pos_3);
	insertNode(2, list, pos_4);
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

	/* Test functions 'cloneList' and 'deleteNode' */
	printf("Test functions 'cloneList' and 'deleteNode'\n\n");
	list_1=cloneList(list);
	printf("Before 'deleteNode':\n");
	printList(list_1);
	deleteNode(2, list_1);
	printf("After 'deleteNode':\n");
	printList(list_1);
	printf("\n");

	/* Test function 'getListLength' */
	printf("Test function 'getListLength'\n\n");
	len=getListLength(list);
	printf("Length: %d\n", len);
	printf("\n");

	/* Test functions 'findNode' and 'getNodeIndex' */
	printf("Test functions 'findNode' and 'getNodeIndex'\n\n");
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

	/* Test functions 'getFirstNode', 'getLastNode', 'advanceNode', 'backNode' and 'getNodeElem' */
	printf("Test functions 'getFirstNode', 'getLastNode', 'advanceNode', 'backNode' and 'getNodeElem'\n\n");
	printList(list);
	pos=getFirstNode(list);
	printf("First element at index %d have value %d\n", getNodeIndex(pos, list), getNodeElem(pos));
	pos=getLastNode(list);
	printf("Last element at index %d have value %d\n", getNodeIndex(pos, list), getNodeElem(pos));
	pos=getFirstNode(list);
	pos=advanceNode(pos);
	printf("Second element at index %d have value %d\n", getNodeIndex(pos, list), getNodeElem(pos));
	pos=findNode(3, list);
	if(pos!=NULL)
	{
		pos=backNode(pos);
		printf("Element before 3 have value %d\n", getNodeElem(pos));
	}
	printf("\n");

	/* Test functions 'reverseList' and 'printListReverse' */
	printf("Test functions 'reverseList' and 'printListReverse'\n\n");
	list_3=cloneList(list);
	printf("Before 'reverseList':\n");
	printList(list_3);
	printf("Reverse order\n");
	printListReverse(list_3);
	list_3=reverseList(list_3);
	printf("After 'reverseList':\n");
	printList(list_3);
	printf("Reverse order\n");
	printListReverse(list_3);
	printf("\n");

	/* Cleanup memory */
	destroyList(list);
	destroyList(list_1);
	destroyList(list_2);
	destroyList(list_3);

	return 0;
}