#ifndef STACK_LIST_H
#define STACK_LIST_H

/* integer stack using list */
typedef int ElementType;
#define EmptyTOS -1

typedef struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
typedef PtrToNode Position;

struct Node
{
	ElementType m_elem;
	Position m_next;
};

/* Create a record, return position */
Position createRecord();
/* Create a empty stack, return header */
Stack createStack();
/* Return true if 's is empty */
int isStackEmpty(Stack s);
/* Dispose a stack */
void disposeStack(Stack s);
/* Empty a stack */
void makeStackEmpty(Stack s);
/* Push a element at the front of stack */
void pushRecord(ElementType x, Stack s);
/* Return the element at the front of stack */
ElementType getTopRecord(Stack s);
/* Pop the element at the front of stack */
void popRecord(Stack s);
/* Return and pop the element at the front of stack */
int topAndPopRecord(Stack s);

#endif /* STACK_LIST_H */