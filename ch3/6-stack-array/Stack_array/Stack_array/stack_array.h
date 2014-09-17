#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

/* integer stack using array */
typedef int ElementType;
#define EmptyTOS -1
#define MinStackSize 5

struct StackRecord;
typedef struct StackRecord* Stack;
typedef struct StackRecord* Position;

struct StackRecord
{
	int m_capacity;
	int m_top_of_stack;
	ElementType* m_array;
};

/* Create a record, return position */
Position createRecord();
/* Create a empty stack */
Stack createStack(int max_elements);
/* Return true if 's' is empty */
int isStackEmpty(Stack s);
/* Return true if 's' is full */
int isStackFull(Stack s);
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

#endif /* STACK_ARRAY_H */