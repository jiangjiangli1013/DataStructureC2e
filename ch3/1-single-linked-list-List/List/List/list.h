#ifndef LIST_H
#define LIST_H

/* integer list */
typedef int ElementType;

/* Node */
struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
	ElementType m_elem;
	Position m_next;
};

/* Create a node, return position */
Position createNode();
/* Create a empty list, return header */
List createList();
/* Empty a list */
List makeListEmpty(List list);
/* Return true if 'list' is empty */
int isListEmpty(List list);
/* Return true if 'pos' is the last position in 'list' */
int isNodeLast(Position pos, List list);
/* Return Position of 'x' in 'list', return NULL if not found */
Position findNode(ElementType x, List list);
/* Delete 'x' from 'list' */
void deleteNode(ElementType x, List list);
/* Return Position before 'x', return NULL if not found */
Position findNodePrevious(ElementType x, List list);
/* Insert after 'pos' */
void insertNode(ElementType x, List list, Position pos);
/* Append to the last of the list */
void appendNode(ElementType x, List list);
/* Delete all elements of a list */
void deleteList(List list);
/* Destroy a list */
void destroyList(List list);
/* Return header of a list */
Position getHeaderNode(List list);
/* Return Position of first Element */
Position getFirstNode(List list);
/* Return Position of last Element */
Position getLastNode(List list);
/* Return Position after 'pos' */
Position advanceNode(Position pos);
/* Get Element at 'pos' */
ElementType getNodeElem(Position pos);
/* Return length of a list, header not counted */
int getListLength(List list);
/* Return index of current Position, start with 0 (index of the Node header) */
int getNodeIndex(Position pos, List list);
/* Print a list */
void printList(List list);
/* Clone a list, return the new list */
List cloneList(List list);
/* Reverse a list, return the new list */
List reverseList(List list);
/* Swap Field 'Element' in two Positions */
void swapNode(Position pos1, Position pos2, List list);
/* Bubble sort on a list */
void bubbleSortList(List list);
/* Connect two lists, return the new list */
List connectList(List list1, List list2);

#endif /* LIST_H */