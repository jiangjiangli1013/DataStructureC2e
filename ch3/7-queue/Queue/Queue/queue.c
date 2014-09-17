#include "fatal.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

/* Create a record, return position */
Position createRecord()
{
	Position pos;
	pos=(struct QueueRecord* ) malloc(sizeof(struct QueueRecord));

	return pos;
}

/* Create a empty queue, return header */
Queue createQueue(int max_elements)
{
	Queue q;

	if(max_elements<MinQueueSize)
	{
		reportError("Queue size is too small");
	}

	q=createRecord();
	if(q==NULL)
	{
		reportFatalError("Out of space!");
	}

	q->m_array=(ElementType* ) malloc(sizeof(ElementType)*max_elements);
	if(q->m_array==NULL)
	{
		reportFatalError("Out of space!");
	}
	q->m_capacity=max_elements;
	q->m_size=0;
	q->m_front=1;
	q->m_rear=0;

	return q;
}

/* Return true if 'q' is empty */
int isQueueEmpty(Queue q)
{
	return q->m_size==0;
}

/* Return true if Q is full */
int isQueueFull(Queue q)
{
	return q->m_size==q->m_capacity;
}

/* Dispose a queue */
void disposeQueue(Queue q)
{
	if(q!=NULL)
	{
		free(q->m_array);
		free(q);
	}
}

/* Empty a queue */
void makeQueueEmpty(Queue q)
{
	q->m_size=0;
	q->m_front=1;
	q->m_rear=0;
}

/* Increment a position, wraparound to the beginning when needed */
static int succRecord(int value, Queue q)
{
	value++;
	if(value==q->m_capacity)
	{
		value=0;
	}
	return value;
}

/* Add 'x' at the end of queue */
void enqueue(ElementType x,Queue q)
{
	if(!isQueueFull(q))
	{
		q->m_size++;
		q->m_rear=succRecord(q->m_rear, q);
		q->m_array[q->m_rear]=x;
	}
	else
	{
		reportError("Full queue");
	}
}

/* Remove element at the front of queue */
void dequeue(Queue q)
{
	if(!isQueueEmpty(q))
	{
		q->m_size--;
		q->m_front=succRecord(q->m_front,q);
	}
	else
	{
		reportError("Empty queue");
	}
}

/* Return element at the front of queue */
int front(Queue q)
{
	if(!isQueueEmpty(q))
	{
		return q->m_array[q->m_front];
	}
	else
	{
		/* -1 indicates empty queue */
		return -1;
	}
}

/* Return and remove element at the front of queue */
int frontAndDequeue(Queue q)
{
	ElementType x;

	x=0;
	if(!isQueueEmpty(q))
	{
		x=q->m_array[q->m_front];
		q->m_size--;
		q->m_front=succRecord(q->m_front,q);
	}
	else
	{
		/* -1 indicates empty queue */
		x=-1;
	}

	return x;
}