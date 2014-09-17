#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

/* integer list */
typedef int ElementType;

/* Node */
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode CircularList;
typedef PtrToNode Position;

struct Node
{
	ElementType m_elem;
	Position m_next;
	Position m_prev;
};

/* Create a node, return position */
Position createNode();
/* Create a empty list, return the first node */
CircularList createList();
/* Empty a list */
CircularList makeListEmpty(CircularList list);
/* Return true if 'list' is empty */
int isListEmpty(CircularList list);
/* Return true if 'pos' is the last position in 'list' */
int isNodeLast(Position pos, CircularList list);
/* Return Position of 'x' in 'list', return NULL if not found */
Position findNode(ElementType x, CircularList list);
/* Delete 'x' from 'list' */
void deleteNode(ElementType x, CircularList list);
/* Insert after 'pos' */
void insertNode(ElementType x, CircularList list, Position pos);
/* Append to the last of the list */
void appendNode(ElementType x, CircularList list);
/* Delete all elements of a list */
void deleteList(CircularList list);
/* Destroy a list */
void destroyList(CircularList list);
/* Return Position of first Element */
Position getFirstNode(CircularList list);
/* Return Position of last Element */
Position getLastNode(CircularList list);
/* Return Position after 'pos' */
Position advanceNode(Position pos);
/* Return Position before 'pos' */
Position backNode(Position pos);
/* Get Element at 'pos' */
ElementType getNodeElem(Position pos);
/* Return length of a list, header not counted */
int getListLength(CircularList list);
/* Return index of current Position, start with 0 (index of the Node header) */
int getNodeIndex(Position pos, CircularList list);
/* Print a list */
void printList(CircularList list);
/* Print a list in reverse order */
void printListReverse(CircularList list);
/* Clone a list, return the new list */
CircularList cloneList(CircularList list);
/* Reverse a list, return the new list */
CircularList reverseList(CircularList list);

#endif /* CIRCULAR_LIST_H */