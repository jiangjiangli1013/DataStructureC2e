#include "fatal.h"
#include "stack_list.h"
#include <stdio.h>
#include <stdlib.h>

/* Create a record, return position */
Position createRecord()
{
	Position pos;
	pos=(struct Node* ) malloc(sizeof(struct Node));

	return pos;
}

/* Create a empty stack, return header */
Stack createStack()
{
	Stack s;

	s=createRecord();
	s->m_next=NULL;

	return s;
}

int isStackEmpty(Stack s)
{
	return s->m_next==NULL;
}

/* Dispose a stack */
void disposeStack(Stack s)
{
	makeStackEmpty(s);
	free(s);
}

/* Empty a stack */
void makeStackEmpty(Stack s)
{
	if(s==NULL)
	{
		reportError("Use CreateStack first");
	}
	else
	{
		while(!isStackEmpty(s))
		{
			popRecord(s);
		}
	}
}

/* Push a element at the front of stack */
void pushRecord(ElementType x, Stack s)
{
	Position tmp_cell;

	tmp_cell=createRecord();
	if(tmp_cell==NULL)
	{
		reportFatalError("Out of space!");
	}
	else
	{
		tmp_cell->m_elem=x;
		tmp_cell->m_next=s->m_next;
		s->m_next=tmp_cell;
	}
}

/* Return the element at the front of stack */
ElementType getTopRecord(Stack s)
{
	if(!isStackEmpty(s))
	{
		return s->m_next->m_elem;
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
	PtrToNode FirstCell;

	if(!isStackEmpty(s))
	{
		FirstCell=s->m_next;
		s->m_next=FirstCell->m_next;
		free(FirstCell);
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
		top=getTopRecord(s);
		popRecord(s);
	}
	else
	{
		/* 'EmptyTOS' indicates empty stack */
		top=EmptyTOS;
	}

	return top;
}
