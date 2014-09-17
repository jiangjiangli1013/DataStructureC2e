#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

/* integer list */
typedef int ElementType;

/* Node */
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode DoubleList;
typedef PtrToNode Position;

struct Node
{
	ElementType m_elem;
	Position m_next;
	Position m_prev;
};

/* Create a node, return position */
Position createNode();
/* Create a empty list, return header */
DoubleList createList();
/* Empty a list */
DoubleList makeListEmpty(DoubleList list);
/* Return true if 'list' is empty */
int isListEmpty(DoubleList list);
/* Return true if 'pos' is the last position in 'list' */
int isNodeLast(Position pos, DoubleList list);
/* Return Position of 'x' in 'list', return NULL if not found */
Position findNode(ElementType x, DoubleList list);
/* Delete 'x' from 'list' */
void deleteNode(ElementType x, DoubleList list);
/* Insert after 'pos' */
void insertNode(ElementType x, DoubleList list, Position pos);
/* Append to the last of the list */
void appendNode(ElementType x, DoubleList list);
/* Delete all elements of a list */
void deleteList(DoubleList list);
/* Destroy a list */
void destroyList(DoubleList list);
/* Return header of a list */
Position getHeaderNode(DoubleList list);
/* Return Position of first Element */
Position getFirstNode(DoubleList list);
/* Return Position of last Element */
Position getLastNode(DoubleList list);
/* Return Position after 'pos' */
Position advanceNode(Position pos);
/* Return Position before 'pos' */
Position backNode(Position pos);
/* Get Element at 'pos' */
ElementType getNodeElem(Position pos);
/* Return length of a list, header not counted */
int getListLength(DoubleList list);
/* Return index of current Position, start with 0 (index of the Node header) */
int getNodeIndex(Position pos, DoubleList list);
/* Print a list */
void printList(DoubleList list);
/* Print a list in reverse order */
void printListReverse(DoubleList list);
/* Clone a list, return the new list */
DoubleList cloneList(DoubleList list);
/* Reverse a list, return the new list */
DoubleList reverseList(DoubleList list);

#endif /* DOUBLE_LIST_H */