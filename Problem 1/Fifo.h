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
 * Holds one PCB in each linked nodes or maybe just the linked PCBs
 * when I see what they look like
 */
typedef struct queue {
	PCB * head;
	PCB * back;
	int size;
}Queue;

/**
 * Pass in the queue and a pointer of the PCB to enqueue
 */
void enqueueFifo(Queue *queue, PCB *pcb);

/**
 * Pass in a queue. Returns and dequeues the head PCB.
 */
PCB *dequeueFifo(Queue *queue);

/**
 * Returns a pointer to the head PCB
 * Should this just be a copy?
 */
PCB *peekFifo(Queue * queue);

/**
 * Is it Empty?
 */
int isEmptyFifo(Queue * queue);

/**
 * Returns a formatted string of all PCBs and their content
 */
char * toStringQueue(Queue * queue);

#endif /* FIFO_H_ */
