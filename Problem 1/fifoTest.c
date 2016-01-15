///*
// * fifoTest.c
// *
// *  Created on: Jan 9, 2016
// *      Author: Tabi
// */
//
//
//#include "Fifo.h"
//
//#include "Pcb.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//
//int main(void) {
//	setvbuf(stdout, NULL, _IONBF, 0);
//	printf("Beginning FIFO Tests\n");
//	srand( time(NULL) );
//	fQ* randQ = (fQ*) malloc(fQSize());
//	int numPcbs = (rand() % 21) + 10;	//rand() % 21 yields values in range [0,20], and adding 10 gives [10,30].
//	int i;
//	//Test enqueuing
//	for (i = 0; i < numPcbs; i++) {
//		PcbPtr randPcb = malloc(sizeof(PcbStr));
//		setPriority(randPcb, rand() % 32);
//		setID(randPcb, i);
//		fifoEnqueue(randQ, randPcb); //Working now
//		printf("%s", fifoToString(randQ));
//		printf("%s\n", toString(randPcb));
//	}
//
//	printf("Press enter for dequeueing Tests\n");
//	getchar();
//	//Test dequeuing
//	for (i = 0; i < numPcbs; i++) {
//		PcbPtr deqPcb = fifoDequeue(randQ);
//		printf("%s", fifoToString(randQ));
//		printf("%s", toString(deqPcb));
//		printf("\n");
//	}
//	return 0;
//}
