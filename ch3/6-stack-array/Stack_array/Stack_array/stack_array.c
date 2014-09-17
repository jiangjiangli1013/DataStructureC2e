#include "fatal.h"
#include "stack_array.h"

#include <stdio.h>
#include <stdlib.h>

/* Create a record, return position */
Position createRecord()
{
	Position pos;
	pos=(struct StackRecord* ) malloc(sizeof(struct StackRecord));

	return pos;
}

/* Create a empty stack, return header */
Stack createStack(int max_elements)
{
	Stack s;

	if(max_elements<MinStackSize)
	{
		reportError("Stack size is too small");
	}

	s=createRecord();
	if(s==NULL)
	{
		reportFatalError("Out of space!");
	}

	s->m_array=(ElementType* ) malloc(sizeof(ElementType)*max_elements);
	if(s->m_array==NULL)
	{
		reportFatalError("Out of space!");
	}
	s->m_capacity=max_elements;
	s->m_top_of_stack=EmptyTOS;

	return s;
}

/* Return true if 's' is empty */
int isStackEmpty(Stack s)
{
	return s->m_top_of_stack==EmptyTOS;
}

/* Return true if 's is full */
int isStackFull(Stack s)
{
	return s->m_top_of_stack==s->m_capacity-1;
}

/* Dispose a stack */
void disposeStack(Stack s)
{
	if(s!=NULL)
	{
		free(s->m_array);
		free(s);
	}
}

/* Empty a stack */
void makeStackEmpty(Stack s)
{
	s->m_top_of_stack=EmptyTOS;
}

/* Push a element at the front of stack */
void pushRecord(ElementType x, Stack s)
{
	if(!isStackFull(s))
	{
		s->m_top_of_stack++; /* increment TopOfStack, a free cell in stack occupied */
		s->m_array[s->m_top_of_stack]=x;
	}
	else
	{
		reportError("Full stack");
	}
}

/* Return the element at the front of stack */
ElementType getTopRecord(Stack s)
{
	if(!isStackEmpty(s))
	{
		return s->m_array[s->m_top_of_stack];
	}
	else
	{
		/* 'EmptyTOS' indicates empty stack */
		return EmptyTOS;
		/* Error("Empty stack"); */
	}
}

/* Pop the element at the front of stack */
void popRecord(Stack s)
{
	if(!isStackEmpty(s))
	{
		s->m_top_of_stack--; /* decrement TopOfStack, a cell in stack freed */
	}
	else
	{
		reportError("Empty stack");
	}
}
/* Return and pop the element at the front of stack */
int topAndPopRecord(Stack s)
{
	int top;

	top=0;
	if(!isStackEmpty(s))
	{
		top=s->m_array[s->m_top_of_stack];
		s->m_top_of_stack--; /* Decrement TopOfStack, a cell in stack freed */
	}
	else
	{
		/* 'EmptyTOS' Indicate empty stack */
		top=EmptyTOS;
		/* Error("Empty stack"); */
	}

	return top;
}