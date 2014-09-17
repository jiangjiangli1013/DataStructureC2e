#ifndef QUEUE_H
#define QUEUE_H

/* integer queue */
typedef int ElementType;
#define MinQueueSize 5

struct QueueRecord;
typedef struct QueueRecord* Queue;
typedef struct QueueRecord* Position;

struct QueueRecord
{
	int m_capacity;
	int m_front;
	int m_rear;
	int m_size;
	ElementType* m_array;
};

/* Create a record, return position */
Position createRecord();
/* Create a empty queue, return header */
Queue createQueue(int max_elements);
/* Return true if 'q' is empty */
int isQueueEmpty(Queue q);
/* Return true if 'q' is full */
int isQueueFull(Queue q);
/* Dispose a queue */
void disposeQueue(Queue q);
/* Empty a queue */
void makeQueueEmpty(Queue q);
/* Increment a position, wraparound to the beginning when needed */
static int succRecord(int value, Queue q);
/* Add 'x' at the end of queue */
void enqueue(ElementType x,Queue q);
/* Remove element at the front of queue */
void dequeue(Queue q);
/* Return element at the front of queue */
int front(Queue q);
/* Return and remove element at the front of queue */
int frontAndDequeue(Queue q);

#endif /* QUEUE_H */