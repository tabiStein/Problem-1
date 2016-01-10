/*
 * fifoTest.c
 *
 *  Created on: Jan 9, 2016
 *      Author: Tabi
 */


#include "fifo.h"

#include "pcb.h"

#include <stdio.h>
#include <stdlib.h>

typedef QueuePtr FifoPtr; //I just want to call it that here

int main(void) {
	FifoPtr randQ = (FifoPtr) malloc(queueSize());
	int numPcbs = (rand() % 21) + 10;	//rand() % 21 yields values in range [0,20], and adding 10 gives [10,30].
	int i;
	//Test enqueuing
	for (i = 0; i < numPcbs; i++) {
		pcbPtr randPcb = (pcbPtr) malloc(pcbSize());
		setPriority(randPcb, rand() % 32);
		setID(randPcb, rand());
		enqueue(randQ, randPcb);
		printf("%s", toString(randQ));
		printf("%s", toString(randPcb));
	}
	//Test dequeuing
	for (i = 0; i < numPcbs; i++) {
		pcbPtr deqPcb = dequeue(randQ);
		printf("%s", toString(randQ));
		printf("%s", toString(deqPcb));
	}
	return 0;
}
