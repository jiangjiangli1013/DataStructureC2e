#include "circular_list.h"
#include "fatal.h"

#include <stdlib.h>

/* Create a node, return position */
Position createNode()
{
	Position pos;

	pos=(struct Node* ) malloc(sizeof(struct Node));

	return pos;
}

/* Create a empty list, return the first node */
CircularList createList()
{
	CircularList list;

	list=createNode();
	/* circularly linked, list->list->list */
	list->m_next=list;
	list->m_prev=list;

	return list;
}

/* Empty a list */
CircularList makeListEmpty(CircularList list)
{
	if(list!=NULL)
	{
		/* delete all nodes. including the first one */
		deleteList(list);
	}
	/* create empty list again */
	list=createList();

	return list;
}

/* Return true if 'list' is empty */
int isListEmpty(CircularList list)
{
	return (list->m_next==list) && (list->m_prev==list);
}

/* Return true if 'pos' is the last position in 'list' */
/* Parameter 'list' is unused in this implementation */
int isNodeLast(Position pos, CircularList list)
{
	return pos->m_next==list;
}

/* Return Position of 'x' in 'list', return NULL if not found */
Position findNode(ElementType x, CircularList list)
{
	Position pos, pos_found;
	int found;

	found=0;
	if(!isListEmpty(list))
	/* when 'list' is not empty */
	{
		/* point to the first node, no header */
		pos=list;
		do
		{
			if(pos->m_elem==x)
			{
				/* when 'x' is found */
				pos_found=pos;
				found=1;
				break;
			}
			pos=advanceNode(pos);
		} while(pos!=list);
		/* when 'x' is not found */
		if(!found)
		{
			pos_found=NULL;
		}
	}
	else
	/* when 'list' is empty */
	{
		pos_found=NULL;
	}

	return pos_found;
}

/* Delete 'x' from 'list' */
/* No header */
void deleteNode(ElementType x, CircularList list)
{
	Position pos, tmp_cell;

	/* 'pos->m_prev' is the previous node of 'x' */
	pos=findNode(x, list);
	if(pos!=NULL)
	{
		/* X is found, delete it */
		tmp_cell=pos->m_prev->m_next;
		pos->m_prev->m_next=tmp_cell->m_next; /* bypass deleted cell */
		free(tmp_cell);
	}
}

/* Insert after 'pos' */
/* No header assumed */
/* parameter 'list' is unused in this implementation */
void insertNode(ElementType x, CircularList list, Position pos)
{
	Position tmp_cell;

	/* insert new element after 'pos' */
	tmp_cell=createNode();
	if(tmp_cell!=NULL)
	{
		tmp_cell->m_elem=x;
		tmp_cell->m_next=pos->m_next;
		pos->m_next->m_prev=tmp_cell;
		pos->m_next=tmp_cell;
		tmp_cell->m_prev=pos;
	}
	else
	{
		reportFatalError("Out of space!");
	}
}

/* Append to the last of the list */
void appendNode(ElementType x, CircularList list)
{
	Position last_node;

	/* find last node */
	last_node=getLastNode(list);
	/* insert new element after last node */
	insertNode(x, list, last_node);
}

/* Delete all elements of a list */
void deleteList(CircularList list)
{
	Position pos, tmp_cell;

	pos=list; /* no header, just the first node */
    do
	{
		tmp_cell=pos->m_next;
		free(pos);
		pos=tmp_cell;
	} while(pos!=list);
}

/* Destroy a list */
void destroyList(CircularList list)
{
	deleteList(list);
}

/* Return Position of first Element */
Position getFirstNode(CircularList list)
{
	return list;
}

/* Return Position of last Element */
Position getLastNode(CircularList list)
{
	Position last_node;

	/* find last node */
	last_node=list;
	do
	{
		last_node=advanceNode(last_node);
	} while(last_node->m_next!=list);

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

/* Return length of a list */
int getListLength(CircularList list)
{
	int count=0;
	Position pos_count;

	/* 'pos_count' point to the first node, no header */
	pos_count=list;
	do
	{
		pos_count=advanceNode(pos_count);
		count++;
	} while(pos_count!=list);

	return count;
}

/* Return index of current Position */
int getNodeIndex(Position pos, CircularList list)
{
	int count;
	int found;

	/* point to the first node */
	count=1;
	found=0;
	/* check whether 'pos' exists */
	if(pos!=NULL)
	{
		Position pos_count;

		/* 'pos_count' point to the first node, no header */
		pos_count=list;
		do
		{
			if(pos_count==pos)
			{
				found=1;
				break;
			}
			pos_count=advanceNode(pos_count);
			count++;
		} while(pos_count!=list);
		return count;
	}
	else
	{
		/* 'pos' is not in list */
		return -1;
	}
}

/* Print a list */
void printList(CircularList list)
{
	Position pos;

	if(!isListEmpty(list))
	{
		/* point to the first node, no header */
		pos=list;
		do
		{
			printf("%d\n",pos->m_elem);
			pos=advanceNode(pos);
		} while(pos!=list);
	}
	else
	{
		printf("List is empty\n");
	}
}

/* Print a list in reverse order */
void printListReverse(CircularList list)
{
	Position pos, last_node;

	if(!isListEmpty(list))
	{
		/* point to the last node */
		last_node=getLastNode(list);
		pos=last_node;
		do
		{
			printf("%d\n",pos->m_elem);
			pos=backNode(pos);
		} while(pos!=last_node);
	}
	else
	{
		printf("List is empty\n");
	}
}

/* Clone a list */
CircularList cloneList(CircularList list)
{
	CircularList list_new;
	Position pos_new;
	Position pos;

	/* create a new empty list */
	list_new=createList();
	/* point to the first node of new list */
	pos_new=list_new;
	/* copy the first node */
	list_new->m_elem=list->m_elem;
	/* point to the second node */
	pos=list->m_next;
	do
	{
		insertNode(pos->m_elem, list_new, pos_new);
		pos=pos->m_next;
		pos_new=pos_new->m_next;
	} while(pos!=list);

	return list_new;
}

/* Reverse a list, return the new list */
CircularList reverseList(CircularList list)
{
	Position previous, current;

	/* first set Node 'previous' as 'list', because 'list' is the terminator of a list */
	previous=list;         /* the first node */
	current=list->m_next;    /* the second node */
	/* the reversal process, the first node as terminator */
	while(1)
	{
		/* reverse the link directions */
		current->m_prev=current->m_next;
		current->m_next=previous;

		/* shift both Node 'previous' and Node 'current' one position afterward */
		/* this shift process is not necessary at the last pass 
		   when Node 'previous' point to the last node of 'list',
		   and Node 'current' point to the first node
		*/
		if(current==list)
		{
			break;
		}
		previous=current;
		current=current->m_prev;
	}
	
	return previous;
}