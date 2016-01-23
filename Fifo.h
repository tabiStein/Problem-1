/*
 * FIFO.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Sean
 */

#ifndef FIFO_H_
#define FIFO_H_
#include "Pcb.h"

/**
 * The queue ADT.
 * Holds PcbStrs as the nodes.
 */
typedef struct queue {
	PcbStr * head;
	PcbStr * back;
	int size;
}fQ;

/**
 * Returns pointer to a new empty Queue
 */
fQ * createfQ();

/**
 * Destroys Queue
 */
void fQDestructor(fQ * queue);

/**
 * Pass in the queue and a pointer of the PcbStr to enqueue
 */
void fifoEnqueue(fQ *queue, PcbStr * pcb);

/**
 * Pass in a queue. Returns and dequeues the head PcbStr.
 */
PcbStr *fifoDequeue(fQ *queue);

/**
 * Returns a pointer to the head PcbStr
 */
PcbStr *fifoPeek(fQ * queue);

/**
 * Is it Empty?
 */
int fifoIsEmpty(fQ * queue);

/**
 * sizeof(fQ)
 */
int fQSize();

/**
 * Returns a formatted string of all PcbStrs and their content
 */
char * fifoToString(fQ * queue);

#endif /* FIFO_H_ */
