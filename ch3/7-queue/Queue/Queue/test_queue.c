#include "vld.h"

#include "queue.h"
#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
	Queue q;

	q=createQueue(10);

	printf("Enqueue 3,1,2,4,3:\n");
	enqueue(3, q);
	enqueue(1, q);
	enqueue(2, q);
	enqueue(4, q);
	enqueue(3, q);

	while(!isQueueEmpty(q))
	{
		printf("Before dequeue(), Front: %d\n", front(q));
		printf("dequeue()\n");
		dequeue(q);
		printf("After dequeue(), Front: %d\n", front(q));
		printf("\n");
	}

	printf("Enqueue 3,1,2,4,3:\n");
	enqueue(3, q);
	enqueue(1, q);
	enqueue(2, q);
	enqueue(4,q);
	enqueue(3, q);

	while(!isQueueEmpty(q))
	{
		printf("Before 'frontAndDequeue', Front: %d\n", frontAndDequeue(q));
		printf("After 'frontAndDequeue', Front: %d\n", frontAndDequeue(q));
		printf("\n");
	}

	disposeQueue(q);

	return 0;
}