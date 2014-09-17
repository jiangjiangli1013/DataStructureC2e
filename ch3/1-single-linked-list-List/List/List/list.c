#include "list.h"
#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>

/* Create a node, return position */
Position createNode()
{
	Position pos;

	pos=(struct Node* ) malloc(sizeof(struct Node));

	return pos;
}

/* Create a empty list, return header */
List createList()
{
	List list;

	list=createNode();
	list->m_next=NULL;

	return list;
}

/* Empty a list */
List makeListEmpty(List list)
{
	if(list!=NULL)
	{
		deleteList(list);
	}
	list->m_next=NULL;

	return list;
}

/* Return true if 'list' is empty */
int isListEmpty(List list)
{
	return list->m_next==NULL;
}

/* Return true if 'pos' is the last position in 'list' */
/* Parameter 'list' is unused in this implementation */
int isNodeLast(Position pos, List list)
{
	return pos->m_next==NULL;
}

/* Return Position of 'x' in 'list', return NULL if not found */
Position findNode(ElementType x, List list)
{
	Position pos;

	pos=list->m_next;
	while(pos!=NULL && pos->m_elem!=x)
	{
		pos=advanceNode(pos);
	}

	return pos;
}

/* Delete 'x' from 'list' */
/* Cell pointed to by 'pos->m_next' is wiped out */
/* Assume that the position is legal */
/* Assume use of a header node */
void deleteNode(ElementType x, List list)
{
	Position pos, tmp_cell;

	/* 'pos' is the previous node of 'x' */
	pos=findNodePrevious(x, list);
	if(!isNodeLast(pos, list)) /* assumption of header use */
	{
		/* 'x' is found, delete it */
		tmp_cell=pos->m_next;
		pos->m_next=tmp_cell->m_next; /* bypass deleted cell */
		free(tmp_cell);
	}
}

/* Return Position before 'x', return NULL if not found */
/* If 'x' is not found, then the 'm_next' filed of returned value is NULL */
/* Assume a header */
Position findNodePrevious(ElementType x, List list)
{
	Position pos;

	pos=list;
	while(pos->m_next!=NULL && pos->m_next->m_elem!=x)
	{
		pos=advanceNode(pos);
	}

	return pos;
}

/* Insert after 'pos' */
/* Header implementation assumed */
/* Parameter 'list' is unused in this implementation */
void insertNode(ElementType x, List list, Position pos)
{
	Position tmp_cell;

	/* insert new element after 'pos' */
	tmp_cell=createNode();
	if(tmp_cell!=NULL)
	{
		tmp_cell->m_elem=x;
		tmp_cell->m_next=pos->m_next;
		pos->m_next=tmp_cell;
	}
	else
	{
		reportFatalError("Out of space!");
	}
}

/* Append to the last of the list */
void appendNode(ElementType x, List list)
{
	Position last_node;

	/* find last node */
	last_node=getLastNode(list);
	/* insert new element after last node */
	insertNode(x, list, last_node);
}

/* Delete all elements of a list */
void deleteList(List list)
{
	Position pos, tmp_cell;

	pos=list->m_next; /* header assumed */
	list->m_next=NULL;
	while(pos!=NULL)
	{
		tmp_cell=pos->m_next;
		free(pos);
		pos=tmp_cell;
	}
}

/* Destroy a list */
void destroyList(List list)
{
	deleteList(list);
	free(list);
}

/* Return header of a list */
Position getHeaderNode(List list)
{
	return list;
}

/* Return Position of first Element */
Position getFirstNode(List list)
{
	return list->m_next;
}

/* Return Position of last Element */
Position getLastNode(List list)
{
	Position last_node;

	/* find last node */
	last_node=list;
	do
	{
		last_node=advanceNode(last_node);
	} while(last_node->m_next!=NULL);

	return last_node;
}

/* Return Position after 'pos' */
Position advanceNode(Position pos)
{
	return pos->m_next;
}

/* get Element at 'pos' */
ElementType getNodeElem(Position pos)
{
	return pos->m_elem;
}

/* Return length of a list, header not counted */
int getListLength(List list)
{
	int count=0;
	Position pos_count;

	/* 'pos_count' point to the first Element */
	pos_count=list->m_next;
	while(pos_count!=NULL)
	{
		pos_count=advanceNode(pos_count);
		count++;
	}

	return count;
}

/* Return index of current Position, start with 0 (index of the Node header) */
int getNodeIndex(Position pos, List list)
{
	/* Check whether 'pos' exists */
	if(pos!=NULL)
	{
		int count=0;
		Position pos_count;

		/* 'pos_count' point to the Node header */
		pos_count=list;
		while(pos_count!=NULL && pos_count!=pos)
		{
			pos_count=advanceNode(pos_count);
			count++;
		}
		return count;
	}
	else
	{
		/* 'pos' is not in 'list' */
		return -1;
	}
}

/* Print a list */
void printList(List list)
{
	Position pos;

	if(!isListEmpty(list))
	{
		pos=list->m_next;
		while(pos!=NULL)
		{
			printf("%d\n",pos->m_elem);
			pos=advanceNode(pos);
		}
	}
	else
	{
		printf("List is empty\n");
	}
}

/* Clone a list, return the new list */
List cloneList(List list)
{
	List list_new;
	Position pos_new;
	Position pos;

	/* create a new empty list */
	list_new=createList();
	/* point to the header of new list */
	pos_new=list_new;
	/* point to the first element of original list */
	pos=list->m_next;
	while(pos!=NULL)
	{
		insertNode(pos->m_elem, list_new, pos_new);
		pos=advanceNode(pos);
		pos_new=advanceNode(pos_new);
	}

	return list_new;
}

/* Reverse a list, return the new list */
List reverseList(List list)
{
	Position previous, current, next;

	/* first set Node 'previous' as NULL, because NULL is the terminator of a list */
	previous=NULL;
	/* first Node 'current' point to the first element */
	current=list->m_next;
	while(current!=NULL)
	{
		/* Node 'next' is after Node 'current' */
		next=current->m_next;
		/* reverse the link directions */
		/* link Node 'previous' as the Next of Node 'current' */
		current->m_next=previous;
		/* shift both Node 'previous' and Node 'current' one position afterward */
		previous=current;
		current=next;
	}
	/* add a dummy header to Node 'previous' */
	list->m_next=previous;
	
	return list;
}

/* Swap Field 'Element' in two Positions */
/* The Nodes itself are not changed */
/* tmp=a; a=b; b=tmp; */
void swapNode(Position pos1, Position pos2, List list)
{
	ElementType tmp;

	tmp=pos1->m_elem;
	pos1->m_elem=pos2->m_elem;
	pos2->m_elem=tmp;
}

/* Bubble sort on a list*/
void bubbleSortList(List list)
{
	Position pos1, pos2, tmp_cell;
	int pass;

	/* The last pass is not needed, so the last node is omitted (when 'pos1->m_next==NULL') */
	/* After every pass, a large value is bubbled to the last part of the array */ 
	pos1=list->m_next;
	pass=0;
	while(pos1->m_next!=NULL)
	{
		pos2=list->m_next;
		/* Some last elements are already sorted, so we sort elements up to Position of index 'getListLength(list)-pass' */
		/* 'pos2', 'pos2->m_next', so we operate 'pos2' on Position of index '1' to Position of index 'getListLength(list)-pass' */
		tmp_cell=list->m_next;
		while(getNodeIndex(tmp_cell,list)!=getListLength(list)-pass)
		{
			tmp_cell=advanceNode(tmp_cell);
		}
		while(pos2!=tmp_cell)
		{
			if(pos2->m_elem>pos2->m_next->m_elem)
			{
				swapNode(pos2, pos2->m_next, list);
			}
			pos2=advanceNode(pos2);
		}
		pos1=advanceNode(pos1);
		pass++;
	}
}

/* Connect two lists, return the new list */
/* Don't modify inputs */
List connectList(List list1, List list2)
{
	/* Clones of L1 and L2 */
	List list1_clone, list2_clone;
	/* Last node of L1, first node of L2 */
	Position list1_last, list2_first;

	list1_clone=cloneList(list1);
	list2_clone=cloneList(list2);

	/* find the last node of 'list1' */
	list1_last=getLastNode(list1_clone);
	/* find the first node of L2 */
	list2_first=getFirstNode(list2_clone);

	/* Delete the bypassed nodes: NULL, list2_clone */
	/* NULL points to nothing, no need to destroy it */
	free(list2_clone);
	/* Connect the first element of 'list2' to the last element of 'list1' */
	list1_last->m_next=list2_first;

	/* We use 'list1_clone' for output , don't destroy it, */
	/* also note that elements of 'list2_clone' have been connected into 'list1_clone', */
	/* so not to destroy 'list2_clone' */

	return list1_clone;
}