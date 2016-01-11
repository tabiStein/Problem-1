/*
 * fifoTest.c
 *
 *  Created on: Jan 9, 2016
 *      Author: Tabi
 */


#include "Fifo.h"

#include "Pcb.h"

#include <stdio.h>
#include <stdlib.h>

typedef fQ FifoPtr; //I just want to call it that here

int main(void) {
	printf("Beginning FIFO Tests");
	FifoPtr *randQ = malloc(fQSize());
	int numPcbs = (rand() % 21) + 10;	//rand() % 21 yields values in range [0,20], and adding 10 gives [10,30].
	int i;
	//Test enqueuing
	for (i = 0; i < numPcbs; i++) {
		PcbStr *randPcb = malloc(sizeof(PcbStr));
		setPriority(randPcb, rand() % 32);
		setID(randPcb, rand());
		//fifoEnqueue(randQ, randPcb); Doesn't cause error but still terminates program at the beginning somehow because c
		printf("%s", fifoToString(randQ));
		printf("%s", toString(randPcb));
	}
	//Test dequeuing
	for (i = 0; i < numPcbs; i++) {
		PcbStr *deqPcb = fifoDequeue(randQ);
		printf("%s", toString(randQ));
		//printf("%s", toString(deqPcb)); breaks here
	}
	return 0;
}
