#include "double_list.h"
#include "fatal.h"

#include <stdlib.h>

/* Create a node, return position */
Position createNode()
{
	Position pos;

	pos=(struct Node* ) malloc(sizeof(struct Node));

	return pos;
}

/* Create a empty list, return header */
DoubleList createList()
{
	DoubleList list;

	list=createNode();
	list->m_next=NULL;

	return list;
}

/* Empty a list */
DoubleList makeListEmpty(DoubleList list)
{
	if(list!=NULL)
	{
		deleteList(list);
	}
	list->m_next=NULL;

	return list;
}

/* Return true if 'list' is empty */
int isListEmpty(DoubleList list)
{
	return list->m_next==NULL;
}

/* Return true if 'pos' is the last position in 'list' */
/* Parameter 'list' is unused in this implementation */
int IsNodeLast(Position pos, DoubleList list)
{
	return pos->m_next==NULL;
}

/* Return Position of 'x' in 'list', return NULL if not found */
Position findNode(ElementType x, DoubleList list)
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
void deleteNode(ElementType x, DoubleList list)
{
	Position pos, tmp_cell;

	/* 'pos->m_prev' is the previous node of 'x' */
	pos=findNode(x, list);
	if(pos!=NULL) /* assumption of header use */
	{
		/* 'x' is found, delete it */
		tmp_cell=pos->m_prev->m_next;
		pos->m_prev->m_next=tmp_cell->m_next; /* bypass deleted cell */
		free(tmp_cell);
	}
}

/* Insert after 'pos' */
/* Header implementation assumed */
/* Parameter 'list' is unused in this implementation */
void insertNode(ElementType x, DoubleList list, Position pos)
{
	Position tmp_cell;

	/* insert new element after 'pos' */
	tmp_cell=createNode();
	if(tmp_cell!=NULL)
	{
		tmp_cell->m_elem=x;
		tmp_cell->m_next=pos->m_next;
		/* note that when 'pos' is the last node, 'pos->m_next=NULL', then 'NULL->m_prev=P' is not valid */
		if(pos->m_next!=NULL)
		{
			pos->m_next->m_prev=tmp_cell;
		}
		pos->m_next=tmp_cell;
		tmp_cell->m_prev=pos;
	}
	else
	{
		reportFatalError("Out of space!");
	}
}

/* Append to the last of the list */
void appendNode(ElementType x, DoubleList list)
{
	Position last_node;

	/* find last node */
	last_node=getLastNode(list);
	/* insert new element after last node */
	insertNode(x, list, last_node);
}

/* Delete all elements of a list */
void deleteList(DoubleList list)
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
void destroyList(DoubleList list)
{
	deleteList(list);
	free(list);
}

/* Return header of a list */
Position getHeaderNode(DoubleList list)
{
	return list;
}

/* Return Position of first Element */
Position getFirstNode(DoubleList list)
{
	return list->m_next;
}

/* Return Position of last Element */
Position getLastNode(DoubleList list)
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

/* Return Position before 'pos' */
Position backNode(Position pos)
{
	return pos->m_prev;
}

/* Get Element at 'pos' */
ElementType getNodeElem(Position pos)
{
	return pos->m_elem;
}

/* Return length of a list, header not counted */
int getListLength(DoubleList list)
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
int getNodeIndex(Position pos, DoubleList list)
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
void printList(DoubleList list)
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

/* Print a list in reverse order */
void printListReverse(DoubleList list)
{
	Position pos;

	if(!isListEmpty(list))
	{
		pos=getLastNode(list);
		while(pos!=list)
		{
			printf("%d\n",pos->m_elem);
			pos=backNode(pos);
		}
	}
	else
	{
		printf("List is empty\n");
	}
}

/* Clone a list */
DoubleList cloneList(DoubleList list)
{
	DoubleList list_new;
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
DoubleList reverseList(DoubleList list)
{
	Position previous, current;

	/* first set Node 'previous' as NULL, because NULL is the terminator of a list */
	previous=NULL;
	/* first Node 'current' point to the first element */
	current=list->m_next;
	while(current!=NULL)
	{
		/* reverse the link directions */
		current->m_prev=current->m_next;
		current->m_next=previous;
		/* shift both Node 'previous' and Node 'current' one position afterward */
		previous=current;
		current=current->m_prev;
	}
	/* add a dummy header to Node 'previous' */
	list->m_next=previous;
	previous->m_prev=list;

	return list;
}