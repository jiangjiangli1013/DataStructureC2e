#include "vld.h"

#include "stack_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	Stack s;

	s=createStack();

	printf("Push 3,1,2,4,3:\n");
	pushRecord(3,s);
	pushRecord(1,s);
	pushRecord(2,s);
	pushRecord(4,s);
	pushRecord(3,s);
	
	while(!isStackEmpty(s))
	{
		printf("Before popRecord(), Top: %d\n", getTopRecord(s));
		printf("popRecord()\n");
		popRecord(s);
		printf("After popRecord(), Top: %d\n", getTopRecord(s));
		printf("\n");
	}

	printf("Push 3,1,2,4,3:\n");
	pushRecord(3,s);
	pushRecord(1,s);
	pushRecord(2,s);
	pushRecord(4,s);
	pushRecord(3,s);

	while(!isStackEmpty(s))
	{
		printf("Before topAndPopRecord(), Top: %d\n", topAndPopRecord(s));
		printf("After topAndPopRecord(), Top: %d\n", topAndPopRecord(s));
		printf("\n");
	}

	disposeStack(s);

	return 0;
}